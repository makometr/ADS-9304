#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"

int main(int argc, char *argv[]) {
    std::string formula;
    if (argc < 2) {
        std::getline(std::cin, formula);
    } else {
        std::string inFile = argv[1];
        std::ifstream in(inFile);
        if (!in.is_open()) {
            std::cerr << "Error: input file can't be open\n";
            return 0;
        }
        std::getline(in, formula);
        in.close();
    }

    for (int i = 0; i < formula.size(); i++)
        if (formula[i] == ' ') {
            formula.erase(i, 1);
            i--;
        }
    if (!Tree::checkString(formula)) {
        std::cerr << "Error: expression is incorrect\n";
        return 0;
    }

    Tree tree(formula);
    tree.transform();
    if (argc < 3) {
        std::cout << tree << '\n';
    } else {
        std::string outFile = argv[2];
        std::ofstream out(outFile);
        if (!out.is_open()) {
            std::cerr << "Error: input file can't be open\n";
            return 0;
        }
        out << tree << '\n';
        out.close();
    }

    return 0;
}
