#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <memory>
#include <ctime>

#include "Smootshort.h"
#include "Node.h"



void generator(const size_t count, std::vector<int>& arr){
    arr.clear();
    srand(time(0));
    for (size_t i = 0; i < count; i++){
        //arr.push_back(rand() % 1000);
        arr.push_back(i);
    }
}



int main(){

    std::string inputString {};
    getline(std::cin, inputString);
    std::stringstream strStream(inputString);
    std::vector<int> vec {};
    std::copy(std::istream_iterator<int>(strStream), {}, back_inserter(vec));

    std::shared_ptr<Smootshort> SortClass(new Smootshort);

    if(vec.size() == 1){
        std::vector<int> testVec {};
        for(int i = 1; i <= vec[0]; i++){
            generator(2 * i, testVec);
            SortClass->smootshort(testVec);
            SortClass->radix(testVec);
        }
    }else{
        SortClass->smootshort(vec);
        for(size_t i = 0; i < vec.size(); i++){
            std::cout << vec[i] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}