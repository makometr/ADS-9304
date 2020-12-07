#include "../libs/RandomBinarySearchTree.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    size_t cntOfTests = std::stoull(std::string(argv[2]));
    if (argc >= 4 && (cntOfTests + 3 == (size_t)argc))
    {
        std::string str = argv[1];
        std::vector<char> arr;
        for (auto it = str.begin(); it != str.end(); ++it)
            arr.push_back(*it);
        RandomBinarySearchTree<char> tree(arr);
        std::stoull(std::string(argv[2]));
        for (size_t i = 0; i < std::stoull(std::string(argv[2])); ++i)
        {
            if (i > 0)
                std::cout << ' ';
            std::cout << tree.taskFindAndInsert(argv[3 + i][0]);
        }
        std::cout << '\n';
    }
    else
        std::cerr << "incorrect input\n";

    return 0;
}