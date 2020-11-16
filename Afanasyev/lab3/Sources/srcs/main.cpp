#include "../libs/BinarySearchTree.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    if (argc >= 2)
    {
        BinarySearchTree<char> treeChar(argv[1]);
        treeChar.simplifyTheFormula();
        std::cout << treeChar;
    }
    return 0;
}