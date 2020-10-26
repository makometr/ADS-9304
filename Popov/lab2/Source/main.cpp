#include <iostream>
#include <fstream>
#include <variant>
#include <vector>
#include <cctype>

#include "Node.h"
#include "List.h"



int main(int argc, char* argv[]){

    setlocale(LC_ALL, "ru");

    if(argc != 3)
    {
        std::cout << "Неверное кол-во аргументов!" << std::endl;
        return 1;
    }

    std::fstream file1(argv[1]);

    if(!file1)
    {
        std::cout << "Файл " << argv[1] << " не может быть открыт на чтение!" << std::endl;
        return 1;
    }

    std::fstream file2(argv[2]);

    if(!file2)
    {
        std::cout << "Файл " << argv[2] << " не может быть открыт на чтение!" << std::endl;
        return 1;
    }

    std::string structList1 {};    // Строка со структурой первого списка.
    std::string valueAtom1 {};     // Строка со значениями атомов.

    std::string structList2 {};
    std::string valueAtom2 {};

    getline(file1, structList1);
    getline(file1, valueAtom1);

    getline(file2, structList2);
    getline(file2, valueAtom2);

    List *list1 = new List(structList1, valueAtom1);
    List *list2 = new List(structList2, valueAtom2);

    if(list1->getFirstElement() == nullptr){

        std::cout << "Неверная структура или кол-во аргументов списка!" << std::endl;
        return 1;
    }

    if(list2->getFirstElement() == nullptr){

        std::cout << "Неверная структура или кол-во аргументов списка!" << std::endl;
        return 1;
    }

    if(*list1 == *list2){
        std::cout << "Списки идентичны!" << std::endl;
    }else{
        std::cout << "Это разные списки!" << std::endl;
    }

    delete list1;
    delete list2;

    return 0;
}