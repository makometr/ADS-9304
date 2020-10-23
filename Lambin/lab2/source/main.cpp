#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "list.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No input file\n";
        return 0;
    }
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "Error: Wrong input file\n";
        return 0;
    }

    std::vector<std::string> text;
    std::string temp;
    while (std::getline(in, temp)) 
        text.push_back(temp);

    for (int i = 0; i < text.size(); i++)
        std::cout << text[i] << '\n';

    in.close();
    for (int i = 0; i < text.size(); i++)
        text[i].pop_back();

    std::regex target("(\n)");
    for (unsigned int i = 0; i < text.size(); i++) {
        text[i] = std::regex_replace(text[i], target, "");
    }

    List *list = new List(text);

    std::string num1, num2;
    if (argc == 3) {
        std::string str;
        str.assign(argv[2]);
        num1 = str.substr(0, str.find(' '));
        num2 = str.substr(str.find(' ') + 1, str.size());
    } else {
        std::cin >> num1 >> num2;
    }
    list->connect(num1, num2);
    std::ofstream out("result.txt");
    out << *list;
    out.close();

    delete list;
    return 0;
}
