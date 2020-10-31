#include <memory>
#include <iostream>
#include <string>
#include <stack>
#include <queue>

template<typename T>
class BinTree;

template<typename T>
class BinTreeNode {
    std::shared_ptr<BinTreeNode> left;
    std::shared_ptr<BinTreeNode> right;
    std::weak_ptr<BinTreeNode> parent;
    T data;
    friend class BinTree<T>;
public:
    BinTreeNode(std::shared_ptr<BinTreeNode> left, std::shared_ptr<BinTreeNode> right, std::shared_ptr<BinTreeNode<T>> parent , T data): left(std::move(left)), right(std::move(right)), parent(std::move(parent)), data(data){
    }
};

template<typename T>
class BinTree {
public:
    BinTree(std::string& str){
        auto iterator = str.cbegin();
        head = strToBinTree(iterator, nullptr);
    }

    ~BinTree() = default;

    BinTree(const BinTree<T> &other) {
        head = copyBinTree(other.head, nullptr);
    }

    BinTree<T>& operator=(const BinTree<T> &other) {
        head = copyBinTree(other.head);
        return *this;
    }

    BinTree(BinTree<T> &&other) {
        head = std::move(other.head);
    }

    BinTree<T>& operator= (BinTree<T> &&other) {
        head = std::move(other.head);
        return *this;
    }

    std::shared_ptr<BinTreeNode<T>> copyBinTree(std::shared_ptr<BinTreeNode<T>> otherHead, std::shared_ptr<BinTreeNode<T>> headParent) {
        if (otherHead == nullptr) {
            return nullptr;
        }

        if (otherHead == head) {
            return head;
        }

        std::shared_ptr<BinTreeNode<T>> curHead = std::make_shared<BinTreeNode<T>>(nullptr, nullptr, headParent, otherHead->data);
        if (otherHead->left != nullptr) {
            curHead->left = copyBinTree(otherHead->left, curHead);
        }

        if (otherHead->right != nullptr) {
            curHead->right = copyBinTree(otherHead->right, curHead);
        }

        return curHead;
    }

    void insert(T dataToInsert){
        if (head == nullptr) {
            head = std::make_shared<BinTreeNode<T>>(nullptr, nullptr, nullptr, dataToInsert);
            return;
        }
        std::queue<std::shared_ptr<BinTreeNode<T>>> queue;
        queue.push(head);
        while (!queue.empty()) {
            std::shared_ptr<BinTreeNode<T>> temp = queue.front();
            queue.pop();
            if (temp->left != nullptr)
                queue.push(temp->left);
            else {
                temp->left = std::make_shared<BinTreeNode<T>>(nullptr, nullptr, temp, dataToInsert);
                return;
            }
            if (temp->right != nullptr)
                queue.push(temp->right);
            else {
                temp->right = std::make_shared<BinTreeNode<T>>(nullptr, nullptr, temp, dataToInsert);
                return;
            }
        }
    }

    std::shared_ptr<BinTreeNode<T>> find(std::shared_ptr<BinTreeNode<T>> curNode, T dataToFind){
        if(!curNode){
            return nullptr;
        }
        std::shared_ptr<BinTreeNode<T>> foundNode = nullptr;
        if(curNode->left != nullptr){
            foundNode = find(curNode->left, dataToFind);
        }
        if(foundNode != nullptr){
            return foundNode;
        }
        if(curNode->right != nullptr){
            foundNode = find(curNode->right, dataToFind);
        }
        if(foundNode != nullptr){
            return foundNode;
        }
        if(curNode->data == dataToFind){
            return curNode;
        }
        return nullptr;
    }

    void deleteNode(T dataToDelete){
        std::shared_ptr<BinTreeNode<T>> NodeToDelete = find(head, dataToDelete);
        if(!NodeToDelete){
            return;
        }
        std::shared_ptr<BinTreeNode<T>> NodeParent = NodeToDelete->parent.lock();
        if(NodeParent == nullptr){
            head = nullptr;
            return;
        }
        if(NodeParent->left != nullptr){
            if(NodeParent->left->data == dataToDelete){
                NodeParent->left = nullptr;
                return;
            }
        }
        if(NodeParent->right != nullptr){
            if(NodeParent->right->data == dataToDelete){
                NodeParent->right = nullptr;
            }
        }
    }

    void printTree(std::shared_ptr<BinTreeNode<T>> curNode) {
        if (!curNode) {
            return;
        }
        printTree(curNode->left);
        std::cout << curNode->data << ' ';
        printTree(curNode->right);
    }

    void printLeaves(std::shared_ptr<BinTreeNode<T>> curNode) {
        if (!curNode) {
            return;
        }
        if ((curNode->left == nullptr) && (curNode->right == nullptr)){
            std::cout << curNode->data << ' ';
        }else{
            printLeaves(curNode->left);
            printLeaves(curNode->right);
        }
    }

    int countLevel (std::shared_ptr<BinTreeNode<T>> curNode, int curLevel, int levelToCount) {
        if (curNode == nullptr){
            return 0;
        }
        if (curLevel == levelToCount){
            return 1;
        }
        if (curLevel < levelToCount) {
            return countLevel(curNode->left, curLevel + 1, levelToCount) +
                   countLevel(curNode->right, curLevel + 1, levelToCount);
        }
	return 0;
    }

    std::shared_ptr<BinTreeNode<T>> strToBinTree(std::string::const_iterator& iterator, std::shared_ptr<BinTreeNode<T>> parent){
        std::shared_ptr<BinTreeNode<T>> root = nullptr;
        iterator++;
        if (*iterator == ')'){
            return  root;
        }
        root = std::make_shared<BinTreeNode<T>>(nullptr, nullptr, parent, *iterator);
        iterator++;
        if (*iterator == '('){
            root->left = strToBinTree(iterator, root);
            iterator++;
        }
        if (*iterator == '('){
            root->right = strToBinTree(iterator, root);
            iterator++;
        }
        return  root;
    }

    std::shared_ptr<BinTreeNode<T>> getHead(){
        return head;
    }

private:
    std::shared_ptr<BinTreeNode<T>> head;
};


bool isCorrect(const std::string& str){
    std::stack<char> Stack;
    if (str[0] != '('){
        return false;
    }
    for (auto iter = str.cbegin();iter != str.cend()-1; iter++){
        if((*iter == '(') && (*(iter+1) == '(')) {
            return false;
        }
        if(*iter != '(' && *iter != ')' && *(iter+1)  != '(' && *(iter+1)  != ')')
            return false;
    }
    for (char i : str){
        if (i == '('){
            Stack.push(i);
        }
        if (i == ')'){
            if (Stack.empty()){
                return false;
            }
            Stack.pop();
        }
    }
    return Stack.empty();
}

int main() {
    std::string treeString;
    std::getline (std::cin, treeString);
    int levelToCount;
    std::cin >> levelToCount;
    if (!isCorrect(treeString)) {
        std::cout << "Tree is not correct\n";
        return 0;
    }
    BinTree<char> binTree(treeString);
    binTree.printLeaves(binTree.getHead());
    std::cout << "\n" << binTree.countLevel(binTree.getHead(), 1, levelToCount) << std::endl;

}

