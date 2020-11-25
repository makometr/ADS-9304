#include "Node.h"
#include <string>
#include <memory>
#include <iostream>

template <typename T>
std::shared_ptr<Node<T>> createBinTree(std::string::const_iterator &it){
    if(*it == '(' || *it == ')'){
        std::cout << "ERROR: incorrect string\n";
        exit(0);
    }
    std::shared_ptr<Node<T>> cur(new Node<T>(*it));
    it++;
    if(*it == '('){
        it++;
        cur->left = createBinTree<T>(it);
        if(*it != ')'){
            std::cout << "ERROR: incorrect string\n";
            exit(0);
        }
        it++;
		if(*it != '(' && *it != '\0' && *it != ')'){
            std::cout << "ERROR: incorrect string\n";
            exit(0);
		}
    }
    if(*it == '('){
        it++;
        cur->right = createBinTree<T>(it);
        if(*it != ')'){
            std::cout << "ERROR: incorrect string\n";
            exit(0);
        }
        it++;
		if(*it != ')' && *it != '\0'){
			std::cout << "ERROR: incorrect string\n";
            exit(0);
		}
	}
    return cur;
}

template <typename T>
void print(const std::shared_ptr<Node<T>> &ptr, int count){
    std::shared_ptr<Node<T>> cur = ptr;
    for(int i=0;i<count;i++)
        std::cout << '\t';
    std::cout << cur->value << '\n';
    count++;
    if(ptr->left != nullptr)
        print(ptr->left, count);
    if(ptr->right != nullptr)
        print(ptr->right, count);

}

template <typename T>
class BinTree{
public:
	std::shared_ptr<Node<T>> first;
	BinTree(std::string tree){
		std::string::const_iterator it = tree.begin();
    		this->first = createBinTree<T>(it);
	}
	void printTree(){
		int count = 0;
    		print(this->first, count);
	}
	~BinTree(){}
};
