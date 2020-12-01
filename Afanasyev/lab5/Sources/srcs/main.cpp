#include "../libs/RandomBinarySearchTree.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    if (argc >= 3)
    {

        std::string str = argv[1];
        std::vector<char> arr;
        for (auto it = str.begin(); it != str.end(); ++it)
            arr.push_back(*it);
        
        RandomBinarySearchTree<char> tree(arr);

        std::cout << tree << '\n'
                  << tree.taskFindAndInsert(argv[2][0]) << '\n'
                  << tree << '\n';
    }
    return 0;
}