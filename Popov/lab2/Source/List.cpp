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

    size_t level = 0;
    size_t count = 0;
    bool flag1 = 0;
    

    for(size_t i = 0; i < structList.size(); i++){

        if(structList[i] == '('){
            
            if(!level){
                firstElement = new Node;
                level++;
                NodePtr.emplace_back(firstElement);
                flag1 = 1;
                continue;
            }

            if(flag1){
                NodePtr[level - 1]->setValue(new Node);
                NodePtr.emplace_back(std::get<Node*>(NodePtr[level - 1]->getValue()));
            }else{
                NodePtr[level]->setNextPtr(new Node);
                NodePtr.emplace_back(NodePtr[level]->getNextPtr());
                flag1 = 1;
            }

            level++;
        }

        if(structList[i] == ')'){

            if(flag1){
                NodePtr[level - 1]->setValue(nullptr);
                flag1 = 0;
            }
            level--;
        }

        if(isalpha(structList[i])){

            if(flag1){
                NodePtr[level - 1]->setValue(new Node(valueAtom[count]));
                NodePtr.emplace_back(std::get<Node*>(NodePtr[level - 1]->getValue()));
            }else{
                NodePtr[level]->setNextPtr(new Node(valueAtom[count]));
                NodePtr.emplace_back(NodePtr[level]->getNextPtr());
            }

            count++;
            flag1 = 0;
        }
    }

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