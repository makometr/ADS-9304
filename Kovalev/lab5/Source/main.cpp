#include <iostream>
#include <string>
#include <sstream>
#include <memory>

template <typename T>
class Node{
public:
    int counter;
    T data;
    std::shared_ptr<Node<T>> left {nullptr};
    std::shared_ptr<Node<T>> right {nullptr};
    Node(){
        counter = 0;
    }
};

template <typename T>
class BSTree {
public:

    std::shared_ptr<Node<T>> head {nullptr};

    BSTree(std::string &input) {
        std::istringstream s(input);
        T elem;
        while (s >> elem) {
            searchAndInsert(elem, head);
        }
    }

    ~BSTree() = default;

    void searchAndInsert(T elem, std::shared_ptr<Node<T>>& ptr) {
        if (!ptr) {
            ptr = std::make_shared<Node<T>>();
            ptr->data = elem;
            ptr->counter = 1;
        } else if (elem < ptr->data) {
            searchAndInsert(elem, ptr->left);
        } else if (elem > ptr->data) {
            searchAndInsert(elem, ptr->right);
        } else {
            ptr->counter++;
        }
    }

    void searchAndDelete(T elem, std::shared_ptr<Node<T>>& ptr){
       if(ptr) {
            if (elem < ptr->data) {
                searchAndDelete(elem, ptr->left);
            } else if (elem > ptr->data) {
                searchAndDelete(elem, ptr->right);
            } else if (elem == ptr->data) {
                if (ptr->counter > 1) {
                    ptr->counter -= 1;
                    return;
                } else {
                    if (!ptr->left && !ptr->right) {//если нет потомков
                        findParent(elem, head);
                        return;
                    } else if (ptr->right) {
                        std::shared_ptr<Node<T>> leftSon = std::make_shared<Node<T>>();
                        leftSon = findMin(ptr->right);
                        T value = leftSon->data;
                        int ct = leftSon->counter;
                        searchAndDelete(leftSon->data, leftSon);
                        ptr->counter = ct;
                        ptr->data = value;
                        return;
                    } else if (ptr->left) {
                        std::shared_ptr<Node<T>> rightSon = std::make_shared<Node<T>>();
                        rightSon = findMax(ptr->left);
                        T value = rightSon->data;
                        int ct = rightSon->counter;
                        searchAndDelete(rightSon->data, rightSon);
                        ptr->counter = ct;
                        ptr->data = value;
                        return;
                    }
                }
            }
       }else{
           std::cout << "There is no element " << elem << " in tree.\n";
       }
    }

    void findParent(T elem, std::shared_ptr<Node<T>> p){
        std::shared_ptr<Node<T>> ptr = p;
        if(ptr) {
            if (ptr->data == elem) {
                return;
            }
            if (ptr->left) {
                if (ptr->left->data == elem) {
                    ptr->left = nullptr;
                }
            }
            if (ptr->right) {
                if (ptr->right->data == elem) {
                    ptr->right = nullptr;
                }
            }
            if (ptr->data < elem) {
                ptr = ptr->right;
                findParent(elem, ptr);
            } else if (ptr->data > elem) {
                ptr = ptr->left;
                findParent(elem, ptr);
            }
        }else{
            return;
        }
    }

    std::shared_ptr<Node<T>> findMin(std::shared_ptr<Node<T>> p){
        std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>();
        temp = p;
        while(temp->left){
            temp = temp->left;
        }
        return temp;
    }

    std::shared_ptr<Node<T>> findMax(std::shared_ptr<Node<T>> p){
        std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>();
        temp = p;
        while(temp->right){
            temp = temp->right;
        }
        return temp;
    }

    void klp(std::shared_ptr<Node<T>> tmp) {
        if (tmp) {
            std::cout << tmp->data << ' ';
            if (tmp->left) klp(tmp->left);
            if (tmp->right) klp(tmp->right);
        }
    }
};

bool digitChecker(std::string& s){
    int len = s.length();
    int counter = 0;
    for(int i = 0; i < len; i++){
        if(isdigit(s[i]) || s[i] == ' '){
            counter++;
        }else{
            break;
        }
    }
    return counter==len;
}

bool charChecker(std::string& s){
    int len = s.length();
    int counter = 0;
    for(int i = 0; i < len; i++){
        if(isalpha(s[i]) || s[i] == ' '){
            counter++;
        }else{
            break;
        }
    }
    return counter==len;
}

int main(int argc, char* argv[]) {
    if(argc < 3){
	std::cout << "Incorrect input!\n";
        return 0;
    }
    std::string input(argv[1]);
    std::string elemsToDelete(argv[2]);
    if(isdigit(input[0])){
        if(digitChecker(input) && digitChecker(elemsToDelete)){
            BSTree<int> BTree(input);
            std::cout << "Before deleting:\n";
            BTree.klp(BTree.head);
            std::cout << '\n';
            std::istringstream s(elemsToDelete);
            int elem;
            while (s >> elem) {
                BTree.searchAndDelete(elem, BTree.head);
            }
            std::cout << "After deleting:\n";
            BTree.klp(BTree.head);
            std::cout << '\n';
        }else{
            std::cout << "Incorrect input!\n";
            return 0;
        }
    }else if(isalpha(input[0])){
        if(charChecker(input) && charChecker(elemsToDelete)){
            BSTree<char> BTree(input);
            std::cout << "Before deleting:\n";
            BTree.klp(BTree.head);
            std::cout << '\n';
            std::istringstream s(elemsToDelete);
            char elem;
            while (s >> elem) {
                BTree.searchAndDelete(elem, BTree.head);
            }
            std::cout << "After deleting:\n";
            BTree.klp(BTree.head);
            std::cout << '\n';
        }else{
            std::cout << "Incorrect input!\n";
            return 0;
        }
    }else{
        std::cout << "Incorrect input!\n";
        return 0;
    }
    std::cout << "Finished successful!\n";
    return 0;
}
