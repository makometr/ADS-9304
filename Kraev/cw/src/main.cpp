#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <memory>
#include <fstream>
#include <getopt.h>
#include <ctime>
#include <cstdlib>

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


std::shared_ptr<Node> createTree1(std::vector<std::shared_ptr<Node>> elems){
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

std::shared_ptr<Node> createTree2(std::vector<std::shared_ptr<Node>> elems){
	int sum1=0, sum2=0;
	std::vector<std::shared_ptr<Node>> vec1,vec2;
	std::shared_ptr<Node> nde = std::make_shared<Node>();
	std::sort(elems.begin(),elems.end(),comp);
	for(int i=0;i<elems.size();i++){
		nde->str += elems[i]->str;
		nde->count += elems[i]->count;
	}
	if(elems.size() != 1){
		while(elems.size() != 0){
			if(sum1>=sum2){
				sum2 += elems[elems.size()-1]->count;
				vec2.push_back(elems[elems.size()-1]);
				elems.pop_back();
			}else{
				sum1 += elems[0]->count;
				vec1.push_back(elems[0]);
				elems.erase(elems.begin());
			}
		}
		nde->left = createTree2(vec1);
		nde->right = createTree2(vec2);
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


std::string genWord(int size){
	std::string str;
	for(int i=0;i<size;i++){
		str.push_back((char)(97 + rand() % 26));
	}
	return str;
}

std::string writeCodes(std::vector<Code> codes, int num){
	std::string str;
	str.push_back(num+48);
	str += ".\n";
	for(int i=0;i<codes.size();i++)
		str +=  codes[i].c + " - " + codes[i].code + "\n";
	str += "\n\n";
	return str;
}

struct Args{
	std::string tasks = "tasks.txt";
	std::string answers = "answers.txt";
	int number = 5;
};

int main(int argc, char** argv){
	
	Args args;
	char* optString = "a:t:hn:?";
	bool a=true;
	int opt = getopt( argc, argv, optString);
    while( opt != -1 ) {
        switch( opt ) {
            case 'a':
               	args.answers = optarg; 
				break;     
            case 't':
                args.tasks = optarg;
				break;
            case 'n':
				args.number = atoi(optarg);
				break;
            case 'h':   
            case '?':
				std::cout << "a - set a file for asnwers\nt - set a file for tasks\nh - display usage\nn - set a number of tasks\n";
                a = false;
				break;
                 
            default:
                break;
        }
        opt = getopt( argc, argv, optString); 
	}

	std::string str;
	std::vector<std::shared_ptr<Node>> vec;
	std::vector<Code> codes;
	std::shared_ptr<Node> head;
	if(a){
	srand(time(0));
	std::ofstream file1, file2;
	file1.open(args.tasks);
	file2.open(args.answers);
	for(int i=0;i<args.number;i++){
		str = genWord(20);
		vec = count0letters(str);
		if(rand()%2){
			head = createTree1(vec);
			file1 << i+1 << ". Закодируйте символы заданной строки по статическому методу Хаффмана.\nСлово: " << str << "\n\n";
		}else{
			head = createTree2(vec);
			file1 << i+1 << ". Закодируйте символы заданной строки по статическому методу Шеннона-Фано.\nСлово: " << str << "\n\n";
		}
		setCodes(head, codes);
		file2 << writeCodes(codes, i+1);
		codes.clear();
	}
	file1.close();
	file2.close();
	}
	return 0;
}




