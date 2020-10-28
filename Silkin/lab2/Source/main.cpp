//Задание 8: Заменить все вхождения элемента x на элемент y

#include <iostream>
#include <string>
#include <iterator>
#include "list.h"

bool isCorrectStr(std::string str) {
    if(str[0] != '(' || str[str.length()-1] != ')') {
        return false;
    }
    int count = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '(') {
            count++;
        }
        if(str[i] == ')') {
            count--;
        }
        if(count < 0) {
            return false;
        }
    }
    if(!count) {
        return true;
    } else {
        return false;
    }
}

int main() {
    std::string expression;
    std::cin >> expression;
    char Old, New;
    std::cin >> Old >> New;
    if(!isCorrectStr(expression)) {
        std::cout << "Incorrect string\n";
        return 0;
    }
    List* list = new List(expression, Old, New);
    return 0;
}