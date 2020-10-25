#include "List.h"
#include "Node.h"

#include <iostream>



List::List(std::string newStructList, std::string valueAtom){

    structList = newStructList;

    checkValue(valueAtom);

    if(!checkStruct()){
        firstElement = nullptr;
    }else{
        createList();
    }
}



List::~List(){
    if(firstElement){
        delete firstElement;
    }
}



void List::checkValue(std::string stringValue){

    // Преобразуем строку в целочисленный вектор значений атомов.
    // Игнорируются все буквы, знаки препинания и тд.

    bool flag = false;

    for(int i = 0; stringValue[i] != '\0'; i++){
        if(isdigit(stringValue[i])){
            if(flag){
                continue;
            }else{
                valueAtom.emplace_back(atoi(&stringValue[i]));
                flag = true;
            }
        }else{
            flag = false;
        }
    }
}



Node* List::getFirstElement(){
    return firstElement;
}



bool List::checkStruct(){
    
    // Проверка строки на корректность.

    int level = 0;
    size_t countAtom = 0;
    size_t count = valueAtom.size();

    if(structList.size() == 0){
        return 0;
    }

    for(size_t i = 0; i < structList.size(); i++){

        if(structList[i] == '('){
            level++;
        }

        if(isalpha(structList[i])){
            countAtom++;
        }

        if(structList[i] == ')'){
            level--;
        }

        if(level < 0){
            return 0;
        }
    }

    if(level != 0){
        return 0;
    }

    if(countAtom != count){
        return 0;
    }

    return 1;
}




void List::createList(){

    // Создание списка на основе полученных данных.

    //size_t level = 0;
    size_t count = 0;
    //bool flag1 = 0;
    int first = 0;
    int second = 0;
    std::string str = structList;
    std::vector<int> vec = valueAtom;
    std::vector<Node*> ptr = NodePtr;
    firstElement = new Node;
    ptr.emplace_back(firstElement);
    
    auto PR = [&second, &str, &vec, &count, &ptr](int first, Node* next, auto &&PR){

        second++;

        if(str[first] == '(' && str[second] == ')'){
            if(second - first == 1){
                next->setValue(nullptr);
            }
            return;
        }

        if(str[first] == '(' && str[second] == '('){
            if(second - first == 1){
                next->setValue(new Node);
                ptr.emplace_back(std::get<Node*>(next->getValue()));
                PR(second, std::get<Node*>(next->getValue()), PR);
            }else{
                Node* tmp = std::get<Node*>(next->getValue());
                for(;;){
                    if(tmp->getNextPtr() == nullptr){
                        break;
                    }else{
                        tmp = tmp->getNextPtr();
                    }
                }
                tmp->setNextPtr(new Node);
                ptr.emplace_back(tmp->getNextPtr());
                PR(second, tmp->getNextPtr(), PR);
            }
        }

        if(str[first] == '(' && isalpha(str[second])){
            if(second - first == 1){
                next->setValue(new Node(vec[count]));
                count++;
                ptr.emplace_back(std::get<Node*>(next->getValue()));
            }else{
                Node* tmp = std::get<Node*>(next->getValue());
                for(;;){
                    if(tmp->getNextPtr() == nullptr){
                        break;
                    }else{
                        tmp = tmp->getNextPtr();
                    }
                }
                tmp->setNextPtr(new Node(vec[count]));
                count++;
                ptr.emplace_back(tmp->getNextPtr());
            }
        }

        PR(first, next, PR);
    };
    
    PR(first, firstElement, PR);
    NodePtr = ptr;
}



bool operator==(const List &l1, const List &l2){

    std::string s1 = l1.structList;
    std::string s2 = l2.structList;
    size_t count1 = 0;
    size_t count2 = 0;

    if(s1.size() == s2.size()){

        for(size_t i = 0; i < s1.size(); i++){

            if(isalpha(s1[i])){
                s1[i] = 'a';
                count1++;
            }
        }

        for(size_t i = 0; i < s2.size(); i++){
            
            if(isalpha(s2[i])){
                s2[i] = 'a';
            }
        }

        if(s1 == s2){

            std::cout << "Идентичные структуры!\n";
            bool flag = 1;

            for(size_t i = 0; i < l1.NodePtr.size(); i++){

                if(std::holds_alternative<int>(l1.NodePtr[i]->getValue()) + std::holds_alternative<int>(l2.NodePtr[i]->getValue()) == 2){

                    if(flag){
                        std::cout << "Кол-во атомов = " << count1 << '\n';
                        std::cout << "Значения атомов:\n";
                        flag = 0;
                    }
                    
                    if(std::get<int>(l1.NodePtr[i]->getValue()) == std::get<int>(l2.NodePtr[i]->getValue())){
                        std::cout << std::get<int>(l1.NodePtr[i]->getValue()) << " == " << std::get<int>(l2.NodePtr[i]->getValue()) << '\n';
                        count2++;
                    }else{
                        std::cout << std::get<int>(l1.NodePtr[i]->getValue()) << " != " << std::get<int>(l2.NodePtr[i]->getValue()) << '\n';
                    }

                }
            }

        }else{
            std::cout << "Различные структуры!\n";
            return 0;
        }

    }else{
        std::cout << "Различные структуры!\n";
        return 0;
    }

    if(count1 == count2){
        return 1;
    }

    return 0;
}



bool operator!=(const List &l1, const List &l2){
    return !(l1 == l2);
}