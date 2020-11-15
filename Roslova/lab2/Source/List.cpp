#include <iostream>
#include <vector>

#include "List.h"
#include "Node.h"



List::List(std::string structList){
    try{
        checkValid(structList);
        createList(structList);
    }catch(const char* strErr){
        std::cerr << strErr << std::endl;
        firstElement = nullptr;
    }
}



std::shared_ptr<Node> List::getFirstElement(){
    return firstElement;
}



void List::revers(){

    auto PR = [](std::shared_ptr<Node>& node, auto&& PR){

        std::shared_ptr<Node> tmp = node;
        std::vector<char> dataAtom {};

        if(!node){
            return;
        }

        while(1){
            if(tmp == nullptr){
                break;
            }
            if(std::holds_alternative<std::shared_ptr<Node>>(tmp->value)){
                PR(std::get<std::shared_ptr<Node>>(tmp->value), PR);
            }else if(std::holds_alternative<char>(tmp->value)){
                dataAtom.emplace_back(std::get<char>(tmp->value));
            }
            tmp = tmp->next;
        }

        tmp = node;

        while(1){
            if(tmp == nullptr){
                break;
            }
            if(std::holds_alternative<char>(tmp->value)){
                tmp->value = dataAtom.back();
                dataAtom.pop_back();
            }
            tmp = tmp->next;
        }

    };

    PR(firstElement, PR);

}



void List::read(){
    
    size_t level = 0;

    auto PR = [&level](std::shared_ptr<Node>& node, auto&& PR){

        std::shared_ptr<Node> tmp = node;

        while(1){
            if(tmp == nullptr){
                if(level){
                    std::cout << ')';
                }
                return;
            }
            if(std::holds_alternative<std::shared_ptr<Node>>(tmp->value)){
                std::cout << '(';
                level++;
                PR(std::get<std::shared_ptr<Node>>(tmp->value), PR);
                level--;
            }else if(std::holds_alternative<char>(tmp->value)){
                std::cout << std::get<char>(tmp->value);
            }
            tmp = tmp->next;
        }

    };
    
    PR(firstElement, PR);
    std::cout << '\n';
}



void List::createList(std::string structList){

    size_t iter = 0;
    size_t secondIter = 0;
    firstElement = std::make_shared<Node>();

    auto PR = [&structList, &secondIter](size_t iter, std::shared_ptr<Node>& node, auto&& PR){

        secondIter++;

        if(structList[iter] == '(' && structList[secondIter] == ')'){
            return;
        }

        if(structList[iter] == '(' && structList[secondIter] == '('){
           
           if(secondIter - iter == 1){
                node->value = std::make_shared<Node>(); 
                PR(secondIter, std::get<std::shared_ptr<Node>>(node->value), PR);
            }else{ 
                std::shared_ptr<Node> tmp = std::get<std::shared_ptr<Node>>(node->value);
                while(tmp->next){
                    tmp = tmp->next;
                }
                tmp->next = std::make_shared<Node>();
                PR(secondIter, tmp->next, PR);
            }

        }

        if(structList[iter] == '(' && isalpha(structList[secondIter])){
            
            if(secondIter - iter == 1){
                node->value = std::make_shared<Node>(structList[secondIter]);
            }else{
                std::shared_ptr<Node> tmp = std::get<std::shared_ptr<Node>>(node->value);
                while(tmp->next){
                    tmp = tmp->next;
                }
                tmp->next = std::make_shared<Node>(structList[secondIter]);
            }
    
        }

        PR(iter, node, PR);
    };

    PR(iter, firstElement, PR);
    
}



void List::checkValid(std::string structList){
    
    size_t lB = 0;  // Левая открывающая скобка
    size_t rB = 0;  // Правая закрывающая
    size_t atm = 0; // Кол-во атомов

    for(size_t i = 0; i < structList.size(); i++){

        if(structList[i] == '('){
            lB++;
        }else if(structList[i] == ')'){
            rB++;
        }else if(isalpha(structList[i])){
            atm++;
        }else{
            throw "Unknown symbol!";
        } 

        if(rB > lB){
            throw "Right brackets > Left braskets!";
        }

    }

    if(rB != lB){
        throw "Left braskets < Right brackets!";
    }
    if(structList[0] != '('){
        throw "First symbol != '('!";
    }
    if(structList[structList.size() - 1] != ')'){
        throw "Last symbol != ')'!";
    }

}