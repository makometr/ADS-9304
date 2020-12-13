#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <memory>
#include <fstream>
#include <getopt.h>

struct Node{
	std::string str;
	int count;
	std::shared_ptr<Node> left = nullptr;
	std::shared_ptr<Node> right = nullptr;
};

struct Code{
	std::string c;
	std::string code;
};

bool comp(const std::shared_ptr<Node> &a, const std::shared_ptr<Node> &b){
	return a->count > b->count;
}

std::vector<std::shared_ptr<Node>> count0letters(const std::string text){
	std::vector<std::shared_ptr<Node>> elems1(256);

	for(int i=0;i<elems1.size();i++){
		elems1[i] = std::make_shared<Node>();
		elems1[i]->str = (char)i;
	}
	for(std::string::const_iterator it = text.begin();it != text.end();it++){
			elems1[*it]->count++;	
	}
	
	std::vector<std::shared_ptr<Node>> elems2;
	for(int i=0;i<elems1.size();i++){
		if(elems1[i]->count)
			elems2.push_back(elems1[i]);
	}
	std::sort(elems2.begin(),elems2.end(),comp);
	return elems2;
}


std::shared_ptr<Node> createTree(std::vector<std::shared_ptr<Node>> &elems){
	std::shared_ptr<Node> nde;
	
	while(elems.size() != 1){
		nde = std::make_shared<Node>();
		nde->count = elems[elems.size()-1]->count + elems[elems.size()-2]->count;
		nde->str = elems[elems.size()-1]->str + elems[elems.size()-2]->str;
		nde->left = elems[elems.size()-1];
		nde->right = elems[elems.size()-2];
		elems.pop_back();
		elems.pop_back();
		elems.push_back(nde);
		std::sort(elems.begin(),elems.end(),comp);
	}
	return nde;
}

void setCodes(const std::shared_ptr<Node> &nde, std::vector<Code>& codes, std::string code = "" ){
	Code cd;
	if(nde->right == nullptr &&  nde->left == nullptr){
		codes.push_back({nde->str, code});
	}
	if(nde->left != nullptr)
		setCodes(nde->left,codes, code+'0');
	if(nde->right != nullptr)
		setCodes(nde->right,codes, code+'1');
	
}


void writeCodes(std::vector<Code> codes, std::string f){
	std::ofstream file;
	file.open(f);
	
	for(int i=0;i<codes.size();i++)
		file << codes[i].c << " - " << codes[i].code << '\n';
	
	if(file.is_open())
		file.close();	
}

void encode(const std::string text, std::vector<Code> codes, std::string f){
	std::ofstream file;
	file.open(f);

	for(std::string::const_iterator it=text.begin();it!=text.end();it++){
		for(int i=0;i<codes.size();i++){
			if(codes[i].c[0] == *it)
				file << codes[i].code;	
		}
	}

	if(file.is_open())
		file.close();	
}

void decode(std::string encodedText, std::string decoded, std::vector<Code> codes){
	std::ofstream file;
	file.open(decoded);
	std::string code;
	
	std::string::const_iterator it = encodedText.begin();
	while(it != encodedText.end()){
		code += *it;
		for(int i=0;i<codes.size();i++){
			if(codes[i].code == code){
				file << codes[i].c;
				code.clear();
			}
		}
		it++;
	}

	if(file.is_open())
		file.close();	
}

std::string readText(std::string file){
	std::ifstream f;
	f.open(file);
	std::string text, line;
	while(getline(f, line)){
		text+=line;
	}
	if(f.is_open())
		f.close();
	return text;
}

struct args{
	bool encodeMode=0;
	bool decodeMode=0;
	std::string oFile="";
	std::string iFile="";
	std::string codes="";
};

std::vector<Code> readCodes(std::string file){
	std::vector<Code> codes;
	std::ifstream f(file);
	std::string line, code, c;
	while(getline(f, line, '\n')){
		c = line[0];
		for(int i = 4;line[i] != '\0';i++)
			code.push_back(line[i]);
		codes.push_back({c,code});
		code.clear();
	}
	
	return codes;
}

int main(int argc, char* argv[]){
	
	const option longOpts[] = {
    { "encode", 1, NULL, 'e' },
    { "decode", 1, NULL, 'd' },
    { "file", 1, NULL, 'f' },
    { "out", 1, NULL, 'o' }
	};
	int longIndex;
	char* optString = "e:d:f:o:";
	args arg;
	char c = getopt_long(argc, argv, optString, longOpts, &longIndex);
	while(c != -1){
		switch(c){
			case 'e':
				arg.encodeMode = 1;
				arg.codes = optarg;
				break;
			case 'd':
				arg.decodeMode = 1;
				arg.codes = optarg;
				break;
			case 'f':
				arg.iFile = optarg;
				break;
			case 'o':
				arg.oFile = optarg;
				break;
			default:
				break;

		}
		c = getopt_long(argc, argv, optString, longOpts, &longIndex);
	}

	try{
		if(arg.decodeMode == arg.encodeMode)
			throw 1;
		if(arg.oFile.size() == 0)
			throw 2;
	}catch(int a){
		if(a == 1)
			std::cout << "ERROR: you must enable 1 of 2 modes\n";
		if(a == 2)
			std::cout << "ERROR: you must set output file\n";
		exit(0);
	}

	std::shared_ptr<Node> nde;
	std::vector<Code> codes;
	std::string text;

	if(arg.encodeMode){
		if(arg.iFile.size() != 0)
			text = readText(arg.iFile);
		else
			std::cin >> text;
		std::vector<std::shared_ptr<Node>> elems = count0letters(text);
		nde = createTree(elems);
		setCodes(nde, codes);
		writeCodes(codes, arg.codes);
		encode(text, codes, arg.oFile);
	}
	if(arg.decodeMode){
		if(arg.iFile.size() == 0){
			std::cout << "ERROR: for decoding mode, you must set the input file\n";
			exit(0);
		}
		text = readText(arg.iFile);
		codes = readCodes(arg.codes);
		decode(text,arg.oFile, codes);
	}
}




