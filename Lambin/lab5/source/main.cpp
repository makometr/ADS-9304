#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>
#include "tree.h"

int main (int argc, char *argv[]) {
    bool isEncode = false, isDecode = false;
    std::string nameInput = "", nameOutput = "";
    bool isDebug = false;
    const char *shortOptions = "f:o:h?";
    option longOptions[] = {
        {"encode", no_argument, nullptr, 0},
        {"decode", no_argument, nullptr, 0},
        {"file", required_argument, nullptr, 'f'},
        {"debug", no_argument, nullptr, 0},
        {"help", no_argument, nullptr, 'h'},
        {0, 0, nullptr, 0}
    };
    int longIndex;
    int option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    while (option != -1) {
        switch (option) {
            case 'f':
                nameInput = optarg;
                break;
            case 'o':
                nameOutput = optarg;
                break;
            case 'h':
            case '?':
                std::cout << "\t--encode\t\tEnable encoding mode\n";
                std::cout << "\t--decode\t\tEnable decoding mode\n";
                std::cout << "\t-f --file <file>\tSpecify the name of the input file\n";
                std::cout << "\t-o <file>\t\tSpecify the name of the output file\n";
                std::cout << "\t--debug\t\t\tEnable debugging mode\n";
                std::cout << "\t-h -? --help\t\tCall help\n";
                return 0;
            case 0:
                if (longOptions[longIndex].name == "encode") {
                    isEncode = true;
                    break;
                }
                if (longOptions[longIndex].name == "decode") {
                    isDecode = true;
                    break;
                }
                if (longOptions[longIndex].name == "debug") {
                    isDebug = true;
                    break;
                }
        }
        option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    }

    std::string str = "";

    if (nameInput.size()) {
        std::ifstream file(nameInput);
        if (!file.is_open()) {
            std::cerr << "Error: Wrong input file\n";
            return 0;
        }
        std::string temp;
        while (std::getline(file, temp)) 
            str += temp;
        file.close();
    } else {
        std::getline(std::cin, str);
    }

    if (isEncode) {
        str = Tree::encode(str, isDebug);
    }
    if (isDecode) {
        Tree::removeSpaces(str);
        str = Tree::decode(str, isDebug);
    }

    if (nameOutput.size()) {
        std::ofstream file(nameOutput);
        file << str;
        file.close();
    } else {
        std::cout << str << '\n';
    }
    return 0;
}
