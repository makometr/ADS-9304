#include <memory>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <sstream>

template<typename T>
class BinTree;

template<typename T>
class BinTreeNode{
public:
    std::shared_ptr<BinTreeNode> left;
    std::shared_ptr<BinTreeNode> right;
    std::weak_ptr<BinTreeNode> parent;
    T data;
    friend class BinTree<T>;
    BinTreeNode(std::shared_ptr<BinTreeNode> left, std::shared_ptr<BinTreeNode> right, const std::shared_ptr<BinTreeNode>& parent , T data): left(std::move(left)), right(std::move(right)), parent(parent), data(data)
    {
    }
};

template<typename T>
class BinTree {
public:
    BinTree(std::vector<T> vec){
        std::sort(vec.begin(), vec.end());
        int counter = 0;
        head = vecToBinTree(vec.size(), counter, vec, nullptr);
    }

    ~BinTree() = default;

    BinTree(const BinTree& other) {
        head = copyBinTree(other.head, nullptr);
    }

    BinTree& operator= (const BinTree& other){
        head = copyBinTree(other.head, nullptr);
        return *this;
    }

    BinTree(BinTree &&other) {
        head = std::move(other.head);
    }

    BinTree& operator= (BinTree &&other) {
        head = std::move(other.head);
        return *this;
    }

    std::shared_ptr<BinTreeNode<T>> copyBinTree(const std::shared_ptr<BinTreeNode<T>>& otherHead, const std::shared_ptr<BinTreeNode<T>>& headParent) {
        if (otherHead == nullptr) {
            return nullptr;
        }

        if (otherHead == head) {
            return head;
        }

        std::shared_ptr<BinTreeNode<T>> curHead = std::make_shared<BinTreeNode>(nullptr, nullptr, headParent, otherHead->data);
        if (otherHead->left != nullptr) {
            curHead->left = copyBinTree(otherHead->left, curHead);
        }

        if (otherHead->right != nullptr) {
            curHead->right = copyBinTree(otherHead->right, curHead);
        }

        return curHead;
    }

    void insert(T data){
        std::vector<T> vec{data};
        collect(getHead(), vec);
        std::sort(vec.begin(), vec.end());
        int counter = 0;
        head = vecToBinTree(vec.size(), counter, vec, nullptr);
    }

    int find(const std::shared_ptr<BinTreeNode<T>>& curNode, T dataToFind){
        if(curNode == nullptr){
            return 0;
        }
        if(dataToFind == curNode->data){
            return find(curNode->left,dataToFind) + find(curNode->right,dataToFind) + 1;
        }
        if(dataToFind < curNode->data)
            return find(curNode->left,dataToFind);
        return find(curNode->right,dataToFind);
    }


    void printTree(const std::shared_ptr<BinTreeNode<T>>& curNode) {
        if (!curNode) {
            return;
        }
        printTree(curNode->left);
        std::cout << curNode->data << ' ';
        printTree(curNode->right);
    }

    void printLevelOrder(const std::shared_ptr<BinTreeNode<T>>& curNode){
        for(int d = 0; d < this->height(this->getHead()); d++){
            printLevel(curNode, d);
            std::cout << "\n";
        }
    }

    void printLevel(const std::shared_ptr<BinTreeNode<T>>& curNode, int level){
        if (curNode == nullptr) {
            std::cout << "_ ";
            return;
        }
        if (level == 0)
            std::cout << curNode->data << ' ';
        else {
            if(level > 0) {
                printLevel(curNode->left, level - 1);
                printLevel(curNode->right, level - 1);
            }
        }
    }


    std::shared_ptr<BinTreeNode<T>> getHead(){
        return head;
    }

    int height(const std::shared_ptr<BinTreeNode<T>>& curNode){
        if(curNode == nullptr){
            return 0;
        }
        if(height(curNode->left) > (height(curNode->right))){
            return height(curNode->left)+1;
        }
        return height(curNode->right)+1;
    }

private:
    std::shared_ptr<BinTreeNode<T>> head;

    std::shared_ptr<BinTreeNode<T>> vecToBinTree(int numOfNodes, int& curNode, const std::vector<T>& vec, const std::shared_ptr<BinTreeNode<T>>& parent){
        if(numOfNodes == 0) {
            return nullptr;
        }
        std::shared_ptr<BinTreeNode<T>> curHead = std::make_shared<BinTreeNode<T>>(nullptr, nullptr, parent, 0);
        curHead->left = vecToBinTree(numOfNodes/2, curNode, vec, curHead);
        curHead->data = vec[curNode];
        curNode++;
        curHead->right = vecToBinTree(numOfNodes - numOfNodes/2 - 1, curNode, vec, curHead);
        return curHead;
    }

    void collect(const std::shared_ptr<BinTreeNode<T>>& curNode,std::vector<T>& vec){
        if(curNode == nullptr){
            return;
        }
        vec.push_back(curNode->data);
        this->collect(curNode->left, vec);
        this->collect(curNode->right, vec);
    }
};

bool checkString(std::string& str){
    auto iterator = str.cbegin();
    while(iterator != str.cend()){
        if(*iterator == '-'){
            iterator++;
        }
        if(!isdigit(*iterator)){
            return false;
        }

        while(isdigit(*iterator)){
            iterator++;
        }

        if((*iterator != ' ') && (iterator != str.cend())){
            return false;
        }

        while(*iterator == ' '){
            iterator++;
        }

    }
    return true;
}

int main() {
    std::string inString{};
    std::getline(std::cin, inString);
    std::vector<int> vecInt;
    if (!checkString(inString)) {
        std::cout << "Incorrect string\n";
        return 0;
    }

    if (!inString.empty()) {
        std::stringstream iss(inString);
        int number;
        while (iss >> number)
            vecInt.push_back(number);
    }
    std::sort(vecInt.begin(), vecInt.end());
    BinTree tree(vecInt);
    int elemToInsert;
    std::cin >> elemToInsert;
    int elemToFind;
    std::cin >> elemToFind;
    tree.insert(elemToInsert);
    tree.printLevelOrder(tree.getHead());
    if(int counter = tree.find(tree.getHead(), elemToFind)){
        std::cout << "Elem " << elemToFind << " found: "<< counter << "\n";
    }else{
        std::cout << "Elem not found" << "\n";
    }
}
