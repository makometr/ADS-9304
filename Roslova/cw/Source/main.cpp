#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <memory>

#include "WeakHeap.h"
#include "customQsort.h"


constexpr auto intervalElement = 2;    // Величина для определения интервала 


void generator(const size_t count, std::vector<int>& arr){      //Данная функция генерирует рандомные значения для вектора arr.
    srand(time(0));
    for (size_t i = 0; i < count; i++){
        arr.push_back(rand() % 1000001);
    }
    std::sort(arr.begin(), arr.end());
}



int main(int argc, char* argv[]){

    std::string inputString {};
    getline(std::cin, inputString);
    std::stringstream ss(inputString);
    std::vector<int> inputVec {};
    std::copy(std::istream_iterator<int>(ss), {}, back_inserter(inputVec));

    auto test = std::make_shared<WeakHeap>();


/*
    Если в массиве > одного элемента, то происходит обычная сортировка.
    Если же кол-во элементов == 1, то данное значение используется для
    формирования набора рандомных тестов.
*/

    if(inputVec.size() > 1){
        test->arr = inputVec;
        test->sortArr();
        for(const auto &a : test->arr){
            std::cout << a << ' ';
        }
        std::cout << std::endl;
    }else if(inputVec.size() == 1){
        if(inputVec[0] <= 0){
            std::cout << "Кол-во тестов не может быть <= 0\n";
        }else{
            for(int i = 1; i <= inputVec[0]; i++){
                generator(intervalElement * i, test->arr);
                test->sortArr();
                customQsort(test->arr);
                test->arr.clear();
            }
        }
    }

    return 0;
} 