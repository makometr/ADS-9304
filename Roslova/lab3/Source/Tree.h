#pragma once 

#include <string>
#include <vector>
#include "Node.h"

#define ARR_SIZE 64  // Не бейте, удобно задавать выделяемые блоки памяти



template<typename base>
class Tree{
    std::vector<Node<base>*> vec;
    bool checkStruct(std::string structTree);
    void createBT(std::string structTree);
public:
    Tree(std::string structTree);
    Tree(Tree<base>&& tree);
    ~Tree();
    Tree<base>& operator=(Tree<base>&& tree);
    std::vector<Node<base>*> getArr();
    void findLeafs();
    void nodesOnLevel(std::string levelFind);
    void addNode(base newData);
    void removeNode(size_t index);
    void lkp();
};



template<typename base>
Tree<base>::Tree(std::string structTree){
    if(!checkStruct(structTree)){
        vec.clear();
    }else{
        vec.resize(ARR_SIZE);
        createBT(structTree);
    }
}



template<typename base>
Tree<base>::Tree(Tree<base>&& tree){
    std::swap(tree->vec, vec);
}



template<typename base>
Tree<base>& Tree<base>::operator=(Tree<base>&& tree){
    vec = std::move(tree->vec);
}


template<typename base>
Tree<base>::~Tree(){

    for(size_t i = 0; i < vec.size(); i++){

        if(vec[i]){
            delete vec[i];
        }

    }
}



template<typename base>
bool Tree<base>::checkStruct(std::string structTree){

    int level = 0;
    int node = 0;

    if(structTree.size() == 0){
        return 0;
    }

    for(size_t i = 0; i < structTree.size(); i++){

        if(isalpha(structTree[i])){
            node++;
        }

        if(structTree[i] == '('){
            level++;
        }

        if(structTree[i] == ')'){
            level--;
            node--;
        }

        if((level - node) < 0){
            return 0;
        }

        if((node - level < -1)){
            return 0;
        }

        if(level < 0){
            return 0;
        }
    }

    if(level != 0){
        return 0;
    }

    if(structTree[0] != '('){
        return 0;
    }

    if(structTree[structTree.size() - 1] != ')'){
        return 0;
    }

    return 1;
}



template<typename base>
void Tree<base>::createBT(std::string structTree){

    size_t first = 0;
    size_t second = 0;
    size_t count = 0;
    size_t arrLevel = 1;
    std::vector<Node<base>*> nodePtr = vec;

    auto PR = [&second, &nodePtr, &structTree, &arrLevel](size_t count, size_t first, auto &&PR){

        second++;
        
        while(count > nodePtr.size() - 1){
            std::vector<Node<base>*> add{};
            arrLevel++;
            add.resize(ARR_SIZE * arrLevel);
            for(size_t i = 0; i < nodePtr.size(); i++){
                if(nodePtr[i] != nullptr){
                    add[i] = nodePtr[i];
                }
            }
            nodePtr = add;
        }
        

        if(structTree[first] == '(' && structTree[second] == ')'){
            return;
        }

        if(structTree[first] == '(' && structTree[second] == '('){

            if(second - first == 2){
                PR((count - 1) * 2 + 1, second, PR);
            }else{
                PR((count - 1) * 2 + 2, second, PR);
            }
        }

        if(structTree[first] == '(' && isalpha(structTree[second])){

            if(!first){
                nodePtr[0] = new Node<base>(structTree[second]);
            }else{
                nodePtr[count] = new Node<base>(structTree[second]);
            }

            count++;
        }

        PR(count, first, PR);
    };

    PR(count, first, PR);
    vec = nodePtr;
}
   


template<typename base>
std::vector<Node<base>*> Tree<base>::getArr(){
    return vec;
}



template<typename base>
void Tree<base>::findLeafs(){

    for(size_t i = 0; i < vec.size(); i++){
        if(vec[i]){
            if(vec[i * 2 + 1] == nullptr && vec[i * 2 + 2] == nullptr){
                std::cout << vec[i]->getData() << " - Лист на позиции " << i << '\n';
            }
        }
    }
}



template<typename base>
void Tree<base>::nodesOnLevel(std::string levelFind){

    size_t level = atoi(levelFind.c_str());

    size_t node1 = 1;
    bool flag = 0;

    if(level > 0){

        for(size_t i = 0; i < level - 1; i++){
            node1 = node1 * 2;
        }

        node1--;

        std::cout << "На уровне " << level << " находятся следующие узлы:\n";

        for(size_t j = 0; j < node1 + 1; j++){

            if(vec[(node1 + j) * 2 + 1] != nullptr){
                flag = 1;
            }

            if(vec[(node1 + j) * 2 + 2] != nullptr){
                flag = 1;
            }

            if(flag){
                
                std::cout << vec[node1 + j]->getData() << " ";
            }
        
            flag = 0;
        }
            
        std::cout << std::endl;

    }else{
        std::cout << "Некорректный уровень!\n";
    }

}



template<typename base>
void Tree<base>::addNode(base newData){
    for(size_t i = 0; i < vec.size(); i++){
        if(vec[i] == nullptr){
            vec[i] = new Node(newData);
            break;
        }
    }
}



template<typename base>
void Tree<base>::removeNode(size_t index){

    if(index > vec.size()){
        std::cout << "Индекс удаления выходит за пределы масива!" << std::endl;
    }else{
        if(vec[index]){
            base newData;
            for(size_t i = vec.size() - 1; i >= 0; i--){
                if(vec[i]){
                    newData = vec[i]->getData();
                    delete vec[i];
                    vec[i] = nullptr;
                    break;
                }
            }
            vec[index]->setData(newData);
        }else{
            std::cout << "Элемент на заданном индексе отсутствует!" << std::endl;
        }
    }
}



template<typename base>
void Tree<base>::lkp(){
    std::vector<Node<base>*> arrNode = vec;
    size_t index = 0;

    auto LKP = [&arrNode](size_t index, auto &&LKP){
        
        if(!arrNode[index]){
            return;
        }else{
            LKP(index * 2 + 1, LKP);
            std::cout << arrNode[index]->getData() << ' ';
            LKP(index * 2 + 2, LKP);
        }
    };

    LKP(index, LKP);
    std::cout << '\n';
}