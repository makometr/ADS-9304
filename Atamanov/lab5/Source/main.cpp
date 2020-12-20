#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <map>
#include <algorithm>
#include <getopt.h>

class BinTreeNode{
public:
    std::shared_ptr<BinTreeNode> left {nullptr};
    std::shared_ptr<BinTreeNode> right {nullptr};
    std::pair<std::string, int> data;

    std::shared_ptr<BinTreeNode> getShannonFanoTree(std::pair<std::string, int> stringWithWeight, std::map<char, int> map, std::map<char, std::string>& codes, std::string code) {
        std::shared_ptr<BinTreeNode> tree = std::make_shared<BinTreeNode>();
        std::pair<std::string, int> left;
        std::pair<std::string, int> right;
        tree->data = stringWithWeight;
        if(stringWithWeight.first.length() == 1) {
            codes.insert({tree->data.first[0], code});
            return tree;
        }
        while (true) {
            if ((left.second + map[stringWithWeight.first[0]]) > (stringWithWeight.second) && left.second == 0) {
                right.first += stringWithWeight.first[0];
                right.second += map[stringWithWeight.first[0]];
                stringWithWeight.second -= map[stringWithWeight.first[0]];
                stringWithWeight.first.erase(0, 1);
                left.first = stringWithWeight.first;
                left.second = stringWithWeight.second;
                break;
            }
            else if((left.second + map[stringWithWeight.first[0]]) > (stringWithWeight.second))
                break;
            else {
                left.first += stringWithWeight.first[0];
                left.second += map[stringWithWeight.first[0]];
                stringWithWeight.second -= map[stringWithWeight.first[0]];
                stringWithWeight.first.erase(0, 1);
            }
        }
        if(right.second == 0) {
            right.first = stringWithWeight.first;
            right.second = stringWithWeight.second;
        }

        if(left.second > right.second)
            std::swap(left, right);
        if (left.second != 0) {
            tree->left = std::make_shared<BinTreeNode>();
            tree->left = getShannonFanoTree(left, map, codes, code + '0');
        }
        if (right.second != 0) {
            tree->right = std::make_shared<BinTreeNode>();
            tree->right = getShannonFanoTree(right, map, codes, code + '1');
        }
        return tree;
    }
};

void getListOfElem(std::map<char, int>& map, std::string::iterator iterator){
    if(*iterator == '\0')
        return;
    while(*iterator != '\0') {
        if (map.find(*iterator) != map.end()) {
            map[*iterator]++;
        } else {
            map.insert({*iterator, 1});
        }
        iterator++;
    }
}

void getStringWithWeigh(std::map<char, int> stringMap, std::pair<std::string, int>& weightString){
    auto iterBeg = stringMap.begin();
    auto iterEnd = stringMap.end();
    std::pair<char, int> max;
    std::map<char, int> finder;
    int flag;
    while(1){
        flag = 0;
        for(;iterBeg != iterEnd;iterBeg++){
            if(iterBeg->second > max.second && finder.find((*iterBeg).first) == finder.end()){
                max.first = (*iterBeg).first;
                max.second = (*iterBeg).second;
                flag = 1;
            }
        }
        iterBeg = stringMap.begin();
        if(flag == 1){
            weightString.first += max.first;
            weightString.second += max.second;
            finder.insert({max.first, max.second});
            max.second = 0;
            continue;
        }
        break;
    }
}

std::string encode(std::string::iterator encodeString){
    std::map<char, int> map;
    std::map<char, std::string> codes;
    std::pair<std::string, int> symbols;
    std::shared_ptr<BinTreeNode> shannonTree;
    std::string code;
    std::string output;

    getListOfElem(map, encodeString);
    getStringWithWeigh(map, symbols);
    shannonTree = shannonTree->getShannonFanoTree(symbols, map, codes, code);

    for(;*encodeString != '\0';encodeString++)
        output += codes[*encodeString];

    std::ofstream outputFile;
    outputFile.open("./Codes.txt");
    auto iterBeg = codes.begin();
    for(iterBeg;iterBeg != codes.end();iterBeg++)
        outputFile << iterBeg->first << ":" << iterBeg->second << ";\n";
    outputFile.close();

    return output;
}

std::string getStringFromFile(const std::string& fileName) {
    std::string stringFile;
    std::ifstream encodeFile;
    encodeFile.open(fileName);
    if (!encodeFile.is_open()){
        std::cout << "Error!\nUndeclared <fileName>.txt\n";
		exit(EXIT_FAILURE);
	}

    std::getline(encodeFile, stringFile);
    encodeFile.close();
    if (stringFile.empty()){
        std::cout << "Error: Empty encode\n";
		exit(EXIT_FAILURE);
	}
    return stringFile;
}

std::map<std::string, char> getCodesFromFile(const std::string& fileName){
    std::map<std::string , char> codes;
    char symbol;
    std::string temp;
    std::string code;
    auto iterBeg = temp.begin();
    std::ifstream file;
    file.open(fileName);
	if(!file.is_open()){
		 std::cout << "Error: Undeclared codeFile";
		 exit(EXIT_FAILURE);
	}
    while(!file.eof()){
        std::getline(file, temp);
        iterBeg = temp.begin();
        symbol = *iterBeg;
        iterBeg += 2;
        while(*iterBeg != ';') {
            code += *iterBeg;
            iterBeg++;
        }
        codes.insert({code, symbol});
        code.clear();
        temp.clear();
    }
    file.close();
    return codes;
}

void decode(const std::string& encode, std::map<std::string, char> codes, int output){
    std::string code;
	std::string fileDescript;
    if(output) {
        std::ofstream decodeFile;
        decodeFile.open("./Output.txt");
        auto iterBeg = encode.begin();
		if(encode.empty()){
			std::cout << "Error!\nUndeclared <fileName>.txt\n";
			exit(EXIT_FAILURE);
		}
        for (; iterBeg != encode.end(); iterBeg++) {
            while (true) {
                code += *iterBeg;
                if (codes.find(code) != codes.end())
                    break;
                else if((iterBeg+1) == encode.end() && codes.find(code) == codes.end()){
					decodeFile << "Error: Wrong codeFile\n";
					exit(EXIT_FAILURE);
				}
				else{
					iterBeg++;
                    continue;
                }
            }
			fileDescript += codes[code];
            code.clear();
        }
		decodeFile << fileDescript << "\n";
		decodeFile.close();
    }
    else{
        auto iterBeg = encode.begin();
        for (iterBeg; iterBeg != encode.end(); iterBeg++) {
            while (true) {
                code += *iterBeg;
                if (codes.find(code) != codes.end())
                    break;
				else if(iterBeg == encode.end() && codes.find(code) == codes.end()){
                    std::cout << "Error: Wrong codeFile\n";
					exit(EXIT_FAILURE);
				}
                else {
                    iterBeg++;
                    continue;
                }
            }
			fileDescript += codes[code];
            code.clear();
        }
		std::cout << fileDescript << "\n";
    }
}

struct Configuration{
    int encode = 0;
    int decode = 0;
	int output = 0;
    std::string codeFile;
    std::string inputFile;
};

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "ru_RU");
    Configuration config;
    char* opts = "e?:d:f:o?:";
    struct option longOpts[]{
            {"encode", no_argument, nullptr, 'e'},
            {"decode", required_argument, nullptr, 'd'},
            {"file", required_argument, nullptr, 'f'},
            {"output", no_argument, nullptr, 'o'},
            {nullptr, 0, nullptr, 0}
    };

    int opt;
    int longIndex;
    opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
    while(opt != -1){
        switch (opt) {
            case 'e':
                config.encode = 1;
                break;
            case 'd':
                config.decode = 1;
                config.codeFile = optarg;
                break;
            case 'f':
                config.inputFile = optarg;
                break;
            case 'o':
                config.output = 1;
                break;
        }
        opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
    }

    if(config.encode == config.decode){
        std::cout << "Error: Must be or 'encode' or 'decode'\n";
		exit(EXIT_FAILURE);
	}
    if(config.encode){
        std::string encodeString;
        std::string encoded;
        if(!config.inputFile.empty()){
            encodeString = getStringFromFile(config.inputFile);
        }
        else
            std::getline(std::cin, encodeString);

        auto iterBeg = encodeString.begin();
        encoded = encode(iterBeg);

        if(config.output){
            std::ofstream output;
            output.open("./Output.txt");
            output << encoded << "\n";
            output.close();
        }
        else
            std::cout << encoded << "\n";
    }

    if(config.decode){
        std::map<std::string, char> codes = getCodesFromFile(config.codeFile);
        std::string encode;
        if(!config.inputFile.empty()) {
            encode = getStringFromFile(config.inputFile);
        }
        else
            std::getline(std::cin, encode);

        decode(encode, codes, config.output);
    }
	
	return 0;
}
