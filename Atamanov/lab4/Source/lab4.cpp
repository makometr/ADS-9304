#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <algorithm>

template <typename base>
void printIntermediate(std::vector<base> futureString, int count){
    std::cout << "[" << count << "]" << ":" << "[";
    for(int i=0;i<futureString.size();i++) {
        if (i == futureString.size() - 1) {
            std::cout << futureString[i];
            break;
        }
        std::cout << futureString[i] << ",";
    }
    std::cout << "]\n";
}
template <typename base>
void modBubble(std::vector<base>& first, int count = 0){
    base temp;
    int minIndex;
    bool sorted;
    std::cout << "[Start array]:";
    printIntermediate(first, count);
    for(int i=0;i<first.size();i++) {
        minIndex = i;
        sorted = true;
        count++;
        for (int j = i; j < first.size() - i - 1; j++) {
            if (first[j] > first[j + 1]) {
                if (first[j] < first[minIndex])
                    minIndex = j;
                std::swap(first[j], first[j + 1]);
                sorted = false;
                std::cout << "[Bubble swap]:";
                printIntermediate(first, count);
            }
            if (first[j] < first[minIndex])
                minIndex = j;
        }
        if(sorted) {
            std::cout << "[Result list]:";
            printIntermediate(first, --count);
            return;
        }
        std::cout << "[Select swap]:";
        std::swap<base>(first[i], first[minIndex]);
        printIntermediate(first, count);
    }
}


template <typename base>
void cocktailSort(std::vector<base>& first, int count = 0){
    int begin = 0;
    int end = first.size()-1;
    bool done;
    std::cout << "[Start array]:";
    printIntermediate(first, count);
    do{
        done = true;
        count++;
        for(int i=begin;i<end;i++){
            if(first[i] > first[i+1]) {
                std::swap(first[i], first[i + 1]);
                std::cout << "[Cocktail r ]:";
                printIntermediate(first, count);
                done = false;
            }
        }
        end--;
        for(int i=end;i>=begin;i--) {
            if (first[i + 1] < first[i]) {
                std::swap(first[i], first[i + 1]);
                std::cout << "[Cocktail l ]:";
                printIntermediate(first, count);
                done = false;
            }
        }
        begin++;
        }while (!done);
    std::cout << "[Result list]:";
    printIntermediate(first, --count);
}

bool isCorrect(std::string::iterator iterator){
    int flag = 0;
    while(*iterator != '\0'){
        if(isdigit(*iterator)) {
            iterator++;
            flag = 0;
        }
        else if(*iterator == ' ' && flag == 0)
            iterator++;
        else if(*iterator == ' ' && flag == 1)
            return false;
        else if(*iterator == '-' && flag == 0) {
            iterator++;
            flag = 1;
        }
        else if(*iterator == '-' && flag == 1)
            return false;
        else
            return false;
    }
    return true;
}

template <typename base>
void printResult(std::vector<base> bubble, std::vector<base> cocktail, std::vector<base> sort){
    std::cout << "[ std::sort ]:[0]:";
    std::cout << "[";
    for(int i=0;i<sort.size();i++){
        if(i == sort.size()-1){
            std::cout << sort[i];
            break;
        }
        std::cout << sort[i] << ",";
    }
    std::cout << "]\n";
    if(std::equal(bubble.begin(), bubble.end(), sort.begin()))
        std::cout << "Comparison of an array sorted using bubble sorting with std::sort was successful\n";
    else
        std::cout << "Comparison of an array sorted using bubble sorting with std::sort failed\n";
    if(std::equal(cocktail.begin(), cocktail.end(), cocktail.begin()))
        std::cout << "Comparison of an array sorted using cocktail sorting with std::sort was successful\n";
    else
        std::cout << "Comparison of an array sorted using cocktail sorting with std:: sort failed\n";
}

int main(){
    std::vector<int> numbers, numbersCopy, stdNumbers;
    std::string vectorString;
    std::getline(std::cin, vectorString);
    auto begin = vectorString.begin();
    if(!isCorrect(begin) || vectorString.empty()){
        std::cout << "Error:\nWrong string format\n";
        exit(EXIT_FAILURE);
    }
    std::stringstream getNum(vectorString);
    int extractNumber;
    while(getNum >> extractNumber)
        numbers.push_back(extractNumber);
    std::cout << "You enter:\n[";
    for(int i=0;i<numbers.size();i++){
        if(i == numbers.size()-1) {
            std::cout << numbers[i];
            break;
        }
        std::cout << numbers[i] << ",";
    }
    std::cout << "]\n";
    numbersCopy = numbers;
    stdNumbers = numbers;
    std::cout << "Modified bubble sort:\n";
    modBubble(numbers);
    std::cout << "Cocktail sort:\n";
    cocktailSort(numbersCopy);
    std::sort(stdNumbers.begin(), stdNumbers.end());
    printResult(numbers, numbersCopy, stdNumbers);
    return 0;
}
