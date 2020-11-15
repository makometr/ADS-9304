#include <memory>
#include <iostream>

#include "Node.h"
#include "List.h"



int main(int argc, char* argv[]){

    std::string structList{};
    getline(std::cin, structList);

    std::unique_ptr<List> myList(new List(structList));

    if(myList->getFirstElement()){
        myList->revers();
        myList->read();
    }

    return 0;
}