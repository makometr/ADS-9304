#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

template<typename T>
void print(std::vector<T>& vec) {
    for (int it : vec) {
        std::cout << it << ' ';
    }
}

template<typename T>
void bingoSort(std::vector<T>& data){
    int maxIndex = size(data)-1;
    T nextMax = data[maxIndex];
    for (int i = maxIndex - 1; i > -1; i--){
        if (data[i] > nextMax) {
            nextMax = data[i];
        }
    }

    while((maxIndex > 0) && (data[maxIndex] == nextMax)){
        maxIndex--;
    }

    T curMax;
    std::cout <<  "Original data: ";
    print(data);
    std::cout <<  "\n";
    std::cout << "First max: " << nextMax << "\n";
    int iterationCounter = 1;
    while(maxIndex > 0){
        curMax = nextMax;
        nextMax = data[maxIndex];
        std::cout << "Iteration: " << iterationCounter << "\n";
        for(int i = maxIndex - 1; i > -1; i--){
            if (data[i] == curMax){
                std::swap(data[i], data[maxIndex]);
                std::cout << "Swapped " << data[i] << " and " << data[maxIndex] << ":\t";
                print(data);
                std::cout << "\n";
                maxIndex--;
            }else{
                if (data[i] > nextMax){
                    nextMax = data[i];
                    std::cout << "Found new next max: " << data[i] << "\n";
                }
            }
        }
        while((maxIndex > 0) && (data[maxIndex] == nextMax)){
            maxIndex--;
        }
        iterationCounter++;
    }
}

bool checkString(std::string& str){
    auto iterator = str.cbegin();
    while(iterator != str.cend()){
        if(*iterator == '-'){
            iterator++;
        }
        if(!isdigit(*iterator)){
            return false;
        }

        while(isdigit(*iterator)){
            iterator++;
        }

        if((*iterator != ' ') && (iterator != str.cend())){
            return false;
        }

        while(*iterator == ' '){
            iterator++;
        }

    }
    return true;
}

int main() {
    std::string inString{};
    std::getline(std::cin, inString);
    std::cout <<  "String: " << inString << "\n";
    if(!checkString(inString) || inString.empty()){
        std::cout << "String is not correct\n";
        return 0;
    }
    std::stringstream iss(inString);
    int number;
    std::vector<int> vec;
    while ( iss >> number )
        vec.push_back(number);
    std::vector<int> copyVec = vec;
    bingoSort(vec);
    std::cout << "\nResult: ";
    print(vec);
    std::cout << "\n";
    std::sort(copyVec.begin(), copyVec.end());
    if (std::equal(vec.cbegin(), vec.cend(),copyVec.cbegin())){
        std::cout << "Compare test with std::sort passed\n";
    }else{
        std::cout << "Compare test with std::sort failed\n";
    }
    return 0;
}

