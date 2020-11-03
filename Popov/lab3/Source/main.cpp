#include <iostream>
#include <vector>
#include <memory>

#define SIZE 128



template <typename Elem>
class Node{
    Elem data;
public:
    Node(Elem newData):data(newData){}
    Elem getData(){
        return data;
    }
};


template <typename Elem>
class Tree{
    std::vector<Node<Elem>*> arrNode;
    void createBinTree(std::string BT){

        size_t first = 0;
        size_t iter = 0;
        size_t count = 0;
        size_t arrLevel = 1;
        std::vector<Node<Elem>*> nodePtr = arrNode;

        auto rec = [&iter, &nodePtr, &BT, &arrLevel](size_t count, size_t first, auto &&rec){

            iter++;

            while(count > nodePtr.size()){
                arrLevel++;
                std::vector<Node<Elem>*> newArr;
                newArr.resize(SIZE * arrLevel);
                for(size_t i = 0; i < nodePtr.size(); i++){
                    if(nodePtr[i] != nullptr){
                        newArr[i] = nodePtr[i];
                    }
                }
                nodePtr = newArr;
            }
            
            if(BT[first] == '(' && BT[iter] == ')'){
                return;
            }

            if(BT[first] == '(' && BT[iter] == '('){
                if(iter - first == 2){
                    rec((count - 1) * 2 + 1, iter, rec);
                }else{
                    rec((count - 1) * 2 + 2, iter, rec);
                }
            }

            if(BT[first] == '(' && isalpha(BT[iter])){

                if(!first){
                    nodePtr[0] = new Node<Elem>(BT[iter]);
                }else{
                    nodePtr[count] = new Node<Elem>(BT[iter]);
                }

                count++;
            }

            rec(count, first, rec);
        };

        rec(count, first, rec);
        arrNode = nodePtr;

    }
    
public:
    Tree(std::string BT){
        arrNode.resize(SIZE);
        createBinTree(BT);
    }
    ~Tree(){
        for(size_t i = 0; i < arrNode.size(); i++){
            if(arrNode[i] != nullptr){
                delete arrNode[i];
            }
        }
    }
    Tree(Tree&& tree){
        std::swap(tree.arrNode, arrNode);
    }
    Tree& operator=(Tree&& tree){
        arrNode = std::move(tree.arrNode);
        return *this;
    }
    void result(std::string findElem){
        if(findElem.size() != 1){
            std::cout << "Некорректный элемент для поиска!" << std::endl;
        }else{
            size_t position = 0;
            size_t count = 0;
            bool flag = 1;
            for(size_t i = 0; i < arrNode.size(); i++){
                if(arrNode[i]){
                    if(arrNode[i]->getData() == *findElem.c_str()){
                        if(flag){
                            std::cout << "Элемент " << findElem << " присутствует в дереве!\n";
                            position = i;
                            flag = 0;
                        }
                        count++;
                    }
                }
            }
            
            if(!flag){
                std::cout << "Число вхождении: " << count << '\n';
                count = 0;
                while(1){
                    if(position == 0){
                        break;
                    }
                    position = (position - 1) / 2;
                    count++;
                }
                std::cout << "Длинна пути до ближайшего элемента: " << count << std::endl;
            }else{
                std::cout << "-1" << std::endl;
            }
        }
    }
    void lkpTrip(){
        std::vector<Node<Elem>*> ptr = arrNode;
        int count = 0;

        auto PR = [&ptr](int count, auto &&PR){
            if(!ptr[count]){
                return;
            }
            PR(count * 2 + 1, PR);
            std::cout << ptr[count]->getData() << ' ';
            PR(count * 2 + 2, PR);
        };

        PR(count,PR);
        std::cout << '\n';
    }
    void newNode(Node<Elem>* node){
        for(size_t i = 0; i < arrNode.size(); i++){
            if(!arrNode[i]){
                arrNode[i] = node;
                break;
            }
        }
    }
    void deleteNode(Elem node){
        int count = 0;
        bool flag = 0;
        for(size_t i = 0; i < arrNode.size(); i++){
            if(arrNode[i]->getData() == node){
                count = i;
                flag = 1;
                break;
            }
        }
        if(flag){
            for(size_t i = arrNode.size() - 1; i >= 0; i--){
                if(arrNode[i]){
                    delete arrNode[count];
                    arrNode[count] = arrNode[i];
                    arrNode[i] = nullptr;
                    break;
                }
            }
        }
    }
};



bool checkBT(std::string inputString){
    int level = 0;
    int node = 0;

    if(inputString.size() == 0){
        return 0;
    }

    for(size_t i = 0; i < inputString.size(); i++){

        if(isalpha(inputString[i])){
            node++;
        }else if(inputString[i] == '('){
            level++;
        }else if(inputString[i] == ')'){
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

    if(inputString[0] != '('){
        return 0;
    }

    if(inputString[inputString.size() - 1] != ')'){
        return 0;
    }

    return 1;
}



int main(int argc, char* argv[]){

    setlocale(LC_ALL, "ru");

    std::string inputString {};
    getline(std::cin, inputString);

    if(!checkBT(inputString)){
        std::cout << "Неверная структура дерева!" << std::endl;
        return -1;
    }

    std::unique_ptr<Tree<char>> BT(new Tree<char>(inputString));

    std::string findElem {};
    getline(std::cin, findElem);

    BT->result(findElem);
    //BT->newNode(new Node('b'));
    //BT->deleteNode('a');
    //BT->lkpTrip();
    

    return 0;
}
