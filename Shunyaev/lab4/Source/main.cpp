
#include <iostream>
#include <algorithm>
#include "HeapSort.h"
#include "Data.h"


bool descending_comp(int a, int b) {
    return a > b;
}


int main()
{
    bool exit = false;
    std::string str;

    while (!exit) {
        std::cout << "Enter data:\n";
        Data data;

        std::cout << "Enter sort mode (min, max):\n";
        std::getline(std::cin, str);
        
        if (str == "min") {
            HeapSort hsort(data, SortMode::MinHeap);
        }
        else if (str == "max") {
            HeapSort hsort(data, SortMode::MaxHeap);
        }

        std::cout << "\n\nTest result\n";
        std::cout << "HeapSort result:  ";
        data.PrintData(data.array_);
       
        if (str == "min") {
            std::sort(data.test_array.begin(), data.test_array.end(), descending_comp);
        }
        else if (str == "max") {
            std::sort(data.test_array.begin(), data.test_array.end());
        }

        std::cout << "\nstd::sort result: ";
        data.PrintData(data.test_array);

        std::cout << "\n\nDo you want to continue (yes, no):\n";
        std::getline(std::cin, str);

        if (str == "no") {
            exit = true;
        }

        std::cout << "\n\n";
    }

    return 0;
}