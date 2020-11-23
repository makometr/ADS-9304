#include "../libs/IterQSort.h"

#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char const *argv[])
{
    std::string str(argv[1]), strCopy = str;

    iterQSort<std::string::iterator>(std::begin(str), std::end(str));

    std::sort(strCopy.begin(), strCopy.end());

    std::cout << "std::sort:\n";
    for (auto it = strCopy.begin(); it != strCopy.end(); ++it)
        std::cout << *it << ' ';

    std::cout << '\n';
    return 0;
}
