#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include <limits.h>
#include <queue>

template<typename T>
class BTree{

    int size = 16;
    bool err = false;
    std::unique_ptr<T[]> treePtr;
    T brk;

public:

    BTree(std::string& s){
        treePtr = std::make_unique<T[]>(size);
        if (std::is_same<T, char>::value) {
            this->brk = CHAR_MIN;
        } else if (std::is_same<T, int>::value) {
            this->brk = INT_MIN;
        }
        for(int i = 0; i < size; i++){
            treePtr[i] = brk;
        }
        /*Считывание дерева в массив*/
        stringToMassive(treePtr, s, 0, s.length(), 0);
    }

    void stringToMassive(std::unique_ptr<T[]>& ptr, std::string& s, int start, int end, int ptrIdx) {
        if(ptrIdx == this->size - 2 || ptrIdx == this->size - 1){
            int newSize = size*2;
            std::unique_ptr<T[]> newPtr = std::make_unique<T[]>(newSize);
            for(int i = 0; i < newSize; i++){
                newPtr[i] = this->brk;
            }
            for(int i = 0; i < this->size; i++){
                newPtr[i] = ptr[i];
            }
            ptr = std::move(newPtr);
            this->size = newSize;
        }
        /*проверка на лист*/
        int brackets = 0;
        for (int i = start + 1; i < end; i++) {
            if (s[i] == '(') {
                brackets++;
            }
        }
        /*если лист - считать и положить в массив*/
        if (!brackets) {
            std::string val = "";
            for (int i = start + 1; i < end; i++) {
                if(s[i] != ' ') {
                    val += s[i];
                }
            }
            if (std::is_same<T, char>::value) {
                if(val != "") {
                    ptr[ptrIdx] = val.c_str()[0];
                }
            } else if (std::is_same<T, int>::value) {
                if(val != "") {
                    ptr[ptrIdx] = atoi(val.c_str());
                }
            }
            return;
        } else {
            /*считываем корень*/
            std::string data = "";
            int leftLeft = 0;
            int rightLeft = 0;
            for (int i = start + 1; i < end; i++) {
                if (s[i] == '(') {
                    leftLeft = i;
                    break;
                }
                if(s[i] != ' ') {
                    data += s[i];
                }
            }
            if (std::is_same<T, char>::value) {
                if(data != "") {
                    ptr[ptrIdx] = data.c_str()[0];
                }
            } else if (std::is_same<T, int>::value) {
                if(data != "") {
                    ptr[ptrIdx] = atoi(data.c_str());
                }
            }
            /*ищем границы левого поддерева*/
            int sum = 0;
            for (int i = leftLeft; i < end; i++) {
                if (s[i] == '(') {
                    sum++;
                }
                if (s[i] == ')') {
                    sum--;
                }
                if (!sum) {
                    rightLeft = i;
                    break;
                }
            }
            /*ищем границы правого поддерева*/
            int j = 0;
            while(s[rightLeft + j] != '('){
                if(rightLeft + j == end){
                    err = 1;
                    break;
                    return;
                }
                j++;
            }
            int leftRight = rightLeft + j, rightRight = 0;
            for (int i = leftRight; i < end; i++) {
                if (s[i] == '(') {
                    sum++;
                }
                if (s[i] == ')') {
                    sum--;
                }
                if (!sum) {
                    rightRight = i;
                    break;
                }
            }
            stringToMassive(ptr, s, leftLeft, rightLeft, 2 * ptrIdx + 1);
            stringToMassive(ptr, s, leftRight, rightRight, 2 * ptrIdx + 2);
        }
    }

    void horizontalTraversal(){
        std::queue<int> treeQueue;
        treeQueue.push(0);
        int it = 0, counter = 1;
        while(!treeQueue.empty()){
            it = treeQueue.front();
            treeQueue.pop();
            std::cout << treePtr[it] << ' ';
            if(treePtr[2*it + 1] != brk){
                treeQueue.push(2*it + 1);
            }
            if(treePtr[2*it + 2] != brk){
                treeQueue.push(2*it + 2);
            }
        }
        std::cout << '\n';
    }

    void printer(){
        for(int i = 0; i < this->size; i++){
            if(treePtr[i] != brk) {
                std::cout << treePtr[i];
            }else{
                std::cout << '#';
            }
        }
        std::cout << '\n';
    }

    void lkpTour(std::unique_ptr<T[]>& ptr, int m = 0){
        if(ptr[m] != brk){
            lkpTour(ptr,2*m + 1);
            std::cout << ptr[m] << '\n';
            lkpTour(ptr,2*m + 2);
        }
    }

    void insertData(T data){
        for(int i = 0; i < size; i++){
            if(treePtr[i] == brk){
                treePtr[i] = data;
                break;
            }
        }
    }

    void deleteData(T data){
        int delIndex = 0;
        for(int i = 0; i < size; i++){
            if(treePtr[i] == data){
                delIndex = i;
                break;
            }
        }

        if(treePtr[delIndex*2 + 1] == brk && treePtr[delIndex*2 + 2] == brk){
            treePtr[delIndex] = brk;
        }
        if(treePtr[delIndex*2 + 1] == brk && treePtr[delIndex*2 + 2] != brk){
            treePtr[delIndex] = treePtr[delIndex*2 + 2];
            treePtr[delIndex*2 + 2] = brk;
        }
        if(treePtr[delIndex*2 + 1] != brk && treePtr[delIndex*2 + 2] == brk){
            treePtr[delIndex] = treePtr[delIndex*2 + 1];
            treePtr[delIndex*2 + 1] = brk;
        }
        if(treePtr[delIndex*2 + 1] != brk && treePtr[delIndex*2 + 2] != brk){
            treePtr[delIndex] = returnChild(delIndex*2 + 1);
        }
    }

    T returnChild(int index){
        if(treePtr[index] == brk){
            return brk;
        }
        T data = treePtr[index];

        treePtr[index] = returnChild(2*index+ 1);

        return data;

    }

    BTree(const BTree<T>& tree):size(tree.size), err(tree.err), brk(tree.brk){
        this->treePtr = std::make_unique<T[]>(tree.size);
        for(int i = 0; i < tree.size; i++){
            this->treePtr[i] = tree.treePtr[i];
        }
    }

    BTree<T>& operator= (BTree<T>& tree){
        if (this == &tree) {
            return *this;
        }
        this->err = tree.getError();

        for(int i = 0; i < tree.getSize(); i++){
            this->treePtr[i] = tree.getPtr()[i];
        }
        this->size = tree.getSize();
        this->brk = tree.getBrk();

        return *this;
    }

    int getSize () {
        return size;
    }

    bool getError() {
        return err;
    }

    std::unique_ptr<T[]>& getPtr() {
        return treePtr;
    }

    T getBrk() {
        return brk;
    }

};

bool checker(std::string & s){
    if(s[0] != '(' || s[s.length() - 1] != ')'){
        return false;
    }

    std::string inside = "";

    for(int i = 1; i < s.length() - 1; i++){
        if(s[i] != ' '){
            inside+=s[i];
        }
    }

    if(inside.empty()){
        return false;
    }

    int brackets = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '('){
            brackets++;
        }
        if(s[i] == ')'){
            brackets--;
            if(brackets < 0){
                return false;
            }
        }
    }
    if(brackets){
        return false;
    }

    std::string father = "";
    for(int i = 1; i < s.length(); i++){
        if(s[i] == '('){
            break;
        }
        if(s[i] != ' ') {
            father += s[i];
        }
    }

    if(father.empty()){
        return false;
    }

    std::string brs = "";
    int i = 0;
    while(i < s.length()){
        if(s[i] == '('){
            brs += s[i];
        }
        if(s[i] == ')'){
            if(brs.empty()){
                return false;
            }else {
                int m = brs.length();
                brs.erase(m - 1, 1);
            }
        }
        i++;
    }

    return true;
}

int main(int argc, char* argv[]){
    
    if(argc < 2){
        std::cout << "Incorrect string!" << '\n';
        return 0;
    }
    
    std::string s(argv[1]);

    std::string type = "";
    type += s[s.length() - 1];
    s.erase(s.length() - 2);

    if(type != "c" && type != "i") {
        std::cout << "Incorrect string!" << '\n';
        return 0;
    }

    if(!checker(s)){
        std::cout << "Incorrect string!" << '\n';
        return 0;
    }

    if(type == "c"){
        BTree<char> BinaryTree(s);
        if(BinaryTree.getError()){
            std::cout << "Incorrect string!" << '\n';
            return 0;
        }else{
            //BinaryTree.printer();
            BinaryTree.horizontalTraversal();
        }

    }else if (type == "i"){
        BTree<int> BinaryTree(s);
        if(BinaryTree.getError()){
            std::cout << "Incorrect string!" << '\n';
            return 0;
        }else{
            //BinaryTree.printer();
            BinaryTree.horizontalTraversal();
        }
    }

    std::cout << "Finished successful!" << '\n';
    return 0;
}

