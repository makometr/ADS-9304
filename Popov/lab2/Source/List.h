#pragma once

#include <vector>
#include <string>
#include <iostream>



class Node;

class List{
    Node* firstElement;             // Адрес первого элемента.
    std::vector<Node*> NodePtr;     // Адреса узлов.
    std::string structList;         // Структура списка.
    std::vector <int> valueAtom;    // Значения атомов.
    void checkValue(std::string stringValue);
    void createList();
    bool checkStruct();
public:
    List(std::string structList, std::string valueAtom);
    ~List();
    Node* getFirstElement();
    friend bool operator==(const List &l1, const List &l2);
    friend bool operator!=(const List &l1, const List &l2);
};