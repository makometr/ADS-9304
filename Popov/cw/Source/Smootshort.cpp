#include <iostream>
#include <memory>
#include <chrono>
#include <fstream>
#include <cmath>
#include <algorithm>

#include "Smootshort.h"
#include "Node.h"



void Smootshort::createLeonardoNumbers(const unsigned sizeVec){
    if(sizeVec <= 1){
        throw "Number of values <= 1";
    }
    unsigned a = 1;
    unsigned b = 1;
    unsigned c = 1;
    while(b <= sizeVec){
        leonardo.emplace_back(b);
        a = b;
        b = c;
        c = a + b + 1;
    }
}



bool Smootshort::isLeonardoNumbers(const size_t digit){
    for(size_t i = 1; i < leonardo.size(); i++){
        if((digit + 1) == leonardo[i]){
            return true;
        }
    }
    return false;
}



void Smootshort::restoreHeap(std::shared_ptr<Node> &node){
    
    auto PR = [](std::shared_ptr<Node> &node, auto &&PR){

        if(!node->left && !node->right){
            return;
        }
        if(node->left->data < node->right->data){
            if(node->data < node->right->data){
                std::swap(node->data, node->right->data);
                PR(node->right, PR);
            }
        }else if(node->left->data > node->right->data){
            if(node->data < node->left->data){
                std::swap(node->data, node->left->data);
                PR(node->left, PR);
            }
        }
    };

    PR(node, PR);
}



void Smootshort::smootshort(std::vector<int> &sortVec){

    try{
        createLeonardoNumbers(sortVec.size());
    
        std::vector<std::shared_ptr<Node>> heap{};

        for(size_t i = 0; i < sortVec.size(); i++){     // Создание леонардовых куч
        
            if(heap.size() >= 2){
                
                if(isLeonardoNumbers(heap[heap.size() - 2]->count + heap[heap.size() - 1]->count)){
                    auto q = std::make_shared<Node>(sortVec[i]);
                    q->left = heap[heap.size() - 2];
                    q->right = heap[heap.size() - 1];
                    q->count = q->left->count + q->right->count + 1;
                    restoreHeap(q);
                    heap.pop_back();
                    heap.pop_back();
                    heap.emplace_back(q);
                    continue;
                }
            }
        
            auto q = std::make_shared<Node>(sortVec[i]);
            heap.emplace_back(q);
        }

        std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

        long position = sortVec.size();
        size_t count;

        while(position){        // Разбираем леонардовы кучи

            count = heap.size() - 1;   
            position--;

            if(heap.size() == 1){                     // Если куча одна - извлекаем корень и разбиваем на подкучи
                std::shared_ptr<Node> tmp = heap[0];
                sortVec[position] = tmp->data;
                heap.pop_back();
                heap.emplace_back(tmp->left);
                heap.emplace_back(tmp->right);
            }else{                                    // Если же несколько, то находим наибольший корень и меняем его со значением последнего элемента
                for(int i = heap.size() - 2; i >= 0; i--){
                    if(heap[heap.size() - 1]->data < heap[i]->data){
                        count = i;
                    }
                }
                if(count != heap.size() - 1){
                    std::swap(heap[heap.size() - 1]->data, heap[count]->data);
                    restoreHeap(heap[count]);
                }
                sortVec[position] = heap[heap.size() - 1]->data;
        
                if(heap[heap.size() - 1]->count > 1){
                    std::shared_ptr<Node> tmp = heap[heap.size() - 1];
                    heap.pop_back();
                    heap.emplace_back(tmp->left);
                    heap.emplace_back(tmp->right);
                }else{
                    heap.pop_back();
                }
            }
        }

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> result = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);

        std::ofstream timeFile("timeSmootshort.txt", std::ios_base::app);

        timeFile << sortVec.size() << ' ';
        timeFile << result.count() * 10'000'000 << '\n';

    }catch(const char* err){
        std::cerr << err << std::endl;
    }
}



void Smootshort::radix(std::vector<int> digitArr){

    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

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

        // Чистим для следующей итерации 
        for(size_t i = 0; i < 10; i++){
            vec[i].clear();
        }
        
    }
    
    for(size_t i = 0; i < digitArr.size(); i++){
        digitArr[i] += nim;
    }

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> result = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);

    std::ofstream timeFile("timeRadix.txt", std::ios_base::app);

    timeFile << digitArr.size() << ' ';
    timeFile << result.count() * 10'000'000 << '\n';
    
}