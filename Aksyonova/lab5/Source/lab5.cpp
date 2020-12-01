#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <sstream>
 
template<typename T>
class Tree;
 
template<typename T>
class Node {
public:
    Node(T data) : left(nullptr), right(nullptr), data(data) {
        height = 1;
    }
 
    Node(std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right, T data) : left(left), right(right), data(data) {
        height = 1;
    }
 
private:
    T data;
    std::shared_ptr<Node<T>> left, right;
    int height;
 
    friend class Tree<T>;
 
};
 
template<typename T>
class Tree {
public:
    Tree(std::vector<T> vec) {
        std::sort(vec.begin(), vec.end());
        root = createNode(vec);
        height = root->height;
    }
 
    std::shared_ptr<Node<T>> copyTree(std::shared_ptr<Node<T>> tree) {
        if (tree->left != nullptr && tree->right != nullptr) {
            std::shared_ptr<Node<T>> node(new Node<T>(copyTree(tree->left), copyTree(tree->right), tree->data));
            return node;
        }
        if (tree->left != nullptr && tree->right == nullptr) {
            std::shared_ptr<Node<T>> node(new Node<T>(copyTree(tree->left), nullptr, tree->data));
            return node;
        }
        if (tree->left == nullptr && tree->right == nullptr) {
            std::shared_ptr<Node<T>> node(new Node<T>(nullptr, nullptr, tree->data));
            return node;
        }
    }
 
    void fixhigh(std::shared_ptr<Node<T>> cur) {
        if (cur->left) {
            fixhigh(cur->left);
        }
        if (cur->right) {
            fixhigh(cur->right);
        }
        if (cur->left == nullptr) {
            cur->height = 1;
        }
        else {
            if (cur->right == nullptr) {
                cur->height = cur->left->height + 1;
            }
            else {
                cur->height = cur->left->height > cur->right->height ? cur->left->height : cur->right->height;
                cur->height++;
            }
        }
    }
 
    Tree(const Tree<T>& tree) {
        std::cout << "I'm a copy constructor!\n";
        root = copyTree(tree.root);
        fixhigh(root);
        height = root->height;
    }
 
    Tree(Tree<T>&& tree) {
        std::cout << "I'm a move constructor!\n";
        std::swap(tree.root, root);
    }
 
    Tree<T>& operator = (const Tree<T>& tree) {
        root = copyTree(tree.root);
        return *this;
    }
 
    Tree<T>& operator = (Tree<T>&& tree) {
        root = std::move(tree.root);
        return *this;
    }
 
    std::shared_ptr<Node<T>> getRoot() {
        return this->root;
    }
 
    bool findAndDelete(T e) {
        if (findElem(root, e)) {
            root = deleteElem(root, e);
            if (root == nullptr) {
                height = 0;
            }
            else {
                height = root->height;
            }
            return true;
        }
        else {
            return false;
        }
    }
 
    bool print() {
        if (!this->height) {
            std::cout << "The tree is empty\n";
            return 0;
        }
        std::cout<<"The AVL-Tree:"<<'\n';
        printElem(root, height);
        return 1;
    }
 
private:
    std::shared_ptr<Node<T>> createNode(std::vector<T> vec) {
        if (vec.size() == 0) {
            return nullptr;
        }
        else {
            int ind = vec.size() / 2;
            auto node = std::make_shared<Node<T>>(vec[ind]);
            std::vector<T> left, right;
            for (int i = 0; i < vec.size(); i++) {
                if (i < ind) {
                    left.push_back(vec[i]);
                }
                if (i > ind) {
                    right.push_back(vec[i]);
                }
            }
            node->left = createNode(left);
            node->right = createNode(right);
            if (node->left == nullptr) {
                node->height = 1;
            }
            else {
                if (node->right == nullptr) {
                    node->height = node->left->height + 1;
                }
                else {
                    node->height = node->left->height > node->right->height ? node->left->height : node->right->height;
                    node->height++;
                }
            }
            return node;
        }
    }
 
    bool findElem(std::shared_ptr<Node<T>> cur, T e) {
        if (cur == nullptr) {
            return false;
        }
        else if (cur->data > e) {
            return findElem(cur->left, e);
        }
        else if (cur->data < e) {
            return findElem(cur->right, e);
        }
        else {
            return true;
        }
    }
 
    std::shared_ptr<Node<T>> findMin(std::shared_ptr<Node<T>> cur) {
        if (cur == nullptr) {
            return nullptr;
        }
        else if (cur->left == nullptr) {
            return cur;
        }
        else {
            return findMin(cur->left);
        }
    }
 
    std::shared_ptr<Node<T>> balanceRight(std::shared_ptr<Node<T>> cur, std::shared_ptr<Node<T>> min) {
        if (cur == nullptr) {
            return nullptr;
        }
        else if (cur->left == nullptr) {
            return cur->right;
        }
        else if (cur->left == min) {
            cur->left = nullptr;
            return balanceTree(cur);
        }
        else {
            cur->left = balanceRight(cur->left, min);
            return balanceTree(cur);
        }
    }
 
    std::shared_ptr<Node<T>> deleteElem(std::shared_ptr<Node<T>> cur, T e) {
        if (cur->data > e) {
            cur->left = deleteElem(cur->left, e);
        }
        else if (cur->data < e) {
            cur->right = deleteElem(cur->right, e);
        }
        else {
            if (cur->right == nullptr) {
                return cur->left;
            }
            else {
                auto min = findMin(cur->right);
                min->right = balanceRight(cur->right, min);
                min->left = cur->left;
                return balanceTree(min);
            }
        }
        return balanceTree(cur);
    }
 
    std::shared_ptr<Node<T>> rotateLeft(std::shared_ptr<Node<T>> cur) {
        auto right = cur->right;
        cur->right = right->left;
        right->left = cur;
        int lHeight = 0, rHeight = 0;
        if (cur->left != nullptr) {
            lHeight = cur->left->height;
        }
        if (cur->right != nullptr) {
            rHeight = cur->right->height;
        }
        cur->height = lHeight > rHeight ? lHeight + 1 : rHeight + 1;
        lHeight = rHeight = 0;
        if (right->left != nullptr) {
            lHeight = right->left->height;
        }
        if (right->right != nullptr) {
            rHeight = right->right->height;
        }
        right->height = lHeight > rHeight ? lHeight + 1 : rHeight + 1;
        return right;
    }
 
    std::shared_ptr<Node<T>> rotateRight(std::shared_ptr<Node<T>> cur) {
        auto left = cur->left;
        cur->left = left->right;
        left->right = cur;
        int lHeight = 0, rHeight = 0;
        if (cur->left != nullptr) {
            lHeight = cur->left->height;
        }
        if (cur->right != nullptr) {
            rHeight = cur->right->height;
        }
        cur->height = lHeight > rHeight ? lHeight + 1 : rHeight + 1;
        lHeight = rHeight = 0;
        if (left->left != nullptr) {
            lHeight = left->left->height;
        }
        if (left->right != nullptr) {
            rHeight = left->right->height;
        }
        left->height = lHeight > rHeight ? lHeight + 1 : rHeight + 1;
        return left;
    }
 
    std::shared_ptr<Node<T>> balanceTree(std::shared_ptr<Node<T>> cur) {
        int lHeight = 0, rHeight = 0;
        if (cur->left != nullptr) {
            lHeight = cur->left->height;
        }
        if (cur->right != nullptr) {
            rHeight = cur->right->height;
        }
        cur->height = lHeight > rHeight ? lHeight + 1 : rHeight + 1;
        int diff = rHeight - lHeight;
        if (diff == 2) {
            int diffRight = 0;
            if (cur->right->left != nullptr) {
                diffRight -= cur->right->left->height;
            }
            if (cur->right->right != nullptr) {
                diffRight += cur->right->right->height;
            }
            if (diffRight < 0) {
                cur->right = rotateRight(cur->right);
            }
            return rotateLeft(cur);
        }
        else if (diff == -2) {
            int diffLeft = 0;
            if (cur->left->left != nullptr) {
                diffLeft -= cur->left->left->height;
            }
            if (cur->left->right != nullptr) {
                diffLeft += cur->left->right->height;
            }
            if (diffLeft > 0) {
                cur->left = rotateLeft(cur->left);
            }
            return rotateRight(cur);
        }
        else {
            return cur;
        }
    }
 
    void printElem(std::shared_ptr<Node<T>> cur, int level) {
        if (cur->left != nullptr) {
            printElem(cur->left, level - 1);
        }
        for (int i = 0; i < level; i++) {
            std::cout << '\t';
        }
        std::cout << cur->data << '\n';
        if (cur->right != nullptr) {
            printElem(cur->right, level - 1);
        }
    }
 
    std::shared_ptr<Node<T>> root;
    int height;
 
};
 
void checkStr(std::string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (!isdigit(str[i]) && str[i] != ' ') {
            str.erase(i, 1);
            i -= 1;
        }
    }
}
 
typedef int elem;
 
int main(int argc, char* argv[]) {
    std::vector<elem> vec;
    std::string str;
    if(argc == 1){
    	std::getline(std::cin, str);
    }
    else if(argc >= 3){
    	str = argv[1];
    }else{
    	std::cout<<"Wrong input";
    	std::cout<<"Finished right\n";
    	return 0;
    }
    checkStr(str);
    std::stringstream ss(str);
    elem value;
    while (ss >> value) {
        vec.push_back(value);
 
        if (ss.peek() == ' ') {
            ss.ignore();
        }
    }
    if(!vec.size()){
    	std::cout<<"The tree is empty\n";
    	std::cout<<"Finished right\n";
    	return 0;
    }
    Tree<elem> tree(vec);
    //Tree<elem> tree1(tree);
    if (!tree.print()) {
    	std::cout<<"Finished right\n";
        return 0;
    }
    //std::cout <<"This is copied tree:\n";
    /*if (!tree1.print()) {
        return 0;
    }*/
    std::string toDelete;
    while (true) {
        std::cout << '\n';
        if(argc == 1){
    		std::cout << "Input element, that you want to delete:\n";
        	std::cin >> toDelete;
    	}else{
    		toDelete = argv[2];
    	}
    	
        if (toDelete == "exit") {
            break;
        }
        checkStr(toDelete);
        
        std::vector<elem> del;
        std::stringstream ss(toDelete);
    	//elem value;
    	while (ss >> value) {
        	del.push_back(value);
 
        	if (ss.peek() == ' ') {
            		ss.ignore();
        	}
    	}
        while(del.size()){
        	elem num = del[0];
        	del.erase(del.begin());
        	std::cout << '\n';
        	if (tree.findAndDelete(num)) {
            		if (!tree.print()) {
            			std::cout<<"Finished right\n";
                		return 0;
            		}
        	}
        	else {
            		std::cout << num << " is not in tree\n";
            		if (!tree.print()) {
            			std::cout<<"Finished right\n";
                		return 0;
            		}
        	}
        }
        if(!del.size()&&argc>=3){
        	std::cout<<"Finished right\n";
        	return 0;
        }
    }
    std::cout<<"Finished right\n";
    return 0;
}
