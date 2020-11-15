#include <iostream>
#include <vector>

#include "customQsort.h"



int main(){

    std::string strValue {};
    getline(std::cin, strValue);

    std::vector<int> arrDigit = convert(strValue);

    if(!arrDigit.empty()){
        customQsort(arrDigit);
    }

    std::cout << "Result: ";
    for(const auto &str : arrDigit){
        std::cout << str << ' ';
    }
    std::cout << std::endl;

    return 0;
}