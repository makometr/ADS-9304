#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include <sstream>
#include <algorithm>


void radix(std::vector<int>& digitArr);     // Поразрядная сортировка



int main(){

    std::string inputString{};
    getline(std::cin, inputString);

    std::stringstream strStream(inputString);
    std::vector<int> vec {};

    std::copy(std::istream_iterator<int>(strStream), {}, back_inserter(vec));

    radix(vec);

    std::cout << "Результат: ";
    for(const auto& digit : vec){
        std::cout << digit << ' ';
    }
    std::cout << std::endl;

    return 0;
}



void radix(std::vector<int>& digitArr){

    int nim = *std::min_element(digitArr.begin(), digitArr.end());

    for(size_t i = 0; i < digitArr.size(); i++){
        digitArr[i] -= nim;
    }
   

    std::vector<std::vector<int>> vec {};   // Для каждого разряда свой блок
    unsigned deegre = 0;                    // Разряд числа
    unsigned level;                         // Позиция блока в массиве
    bool checkRank = 0;                     // Проверка на наличие отличных от 0 рангов
    vec.resize(10);

    while(1){

        // Разбрасываем по соответствующим блокам
        deegre++;
        for(size_t i = 0; i < digitArr.size(); i++){
            level = digitArr[i] / ((int)pow(10, deegre - 1)) % 10;
            if(level){
                checkRank = 1;
            }
            vec[level].emplace_back(digitArr[i]);
        }

        // Перезапись базового вектора
        digitArr.clear();
        for(size_t i = 0; i < vec.size(); i++){
            for(size_t j = 0; j < vec[i].size(); j++){
                digitArr.emplace_back(vec[i][j]);
            }
        }
        
        // Если все элементы в 0 блоке - ливаем
        if(!checkRank){
            break;
        }else{
            checkRank = 0;
        }
        
        // Вывод промежуточного результата
        std::cout << "Итерация " << deegre << ":\n";
        for(size_t i = 0; i < vec.size(); i++){
            if(vec[i].size()){
                std::cout << "Блок " << i << ": [";
                for(size_t j = 0; j < vec[i].size(); j++){
                    std::cout << vec[i][j] + nim << ' ';
                    if(!(j == vec[i].size() - 1)){
                        std::cout << ", ";
                    }
                }
                std::cout << "]\n";
            }
        }
        std::cout << "Объединение блоков: ";
        for(const auto& digit : digitArr){
            std::cout << digit + nim << ' ';
        }
        std::cout << "\n";

        // Чистим для следующей итерации 
        for(size_t i = 0; i < 10; i++){
            vec[i].clear();
        }
        
    }
    
    for(size_t i = 0; i < digitArr.size(); i++){
        digitArr[i] += nim;
    }
    
}