#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <string>
#include <memory>
#include "node.h"
template <typename T>
class Tree {
public:
	std::shared_ptr<Node<T>> root;

	Tree(std::string& str) {
		root = createTree(str);
	}

	Tree(const Tree<T>& tree){
		root = copyTree(tree.root);
	}

	Tree(Tree<T>&& tree){
		std::swap(tree.root, root);
	}

	Tree<T>& operator = (const Tree<T> & tree){
		root = copyTree(tree.root);
		return *this;
	}

	Tree<T>& operator = (Tree<T> && tree){
		root = std::move(tree.root);
		return *this;
	}

	std::shared_ptr<Node<T>> copyTree(std::shared_ptr<Node<T>> tree){
		if (tree->left!=nullptr&&tree->right!=nullptr) {
			std::shared_ptr<Node<T>> node(new Node<T>(copyTree(tree->left), copyTree(tree->right), tree->data));
			return node;
		}
		if (tree->left==nullptr&&tree->right!=nullptr) {
			std::shared_ptr<Node<T>> node(new Node<T>(nullptr, copyTree(tree->right), tree->data));
			return node;
		}
		if (tree->left!=nullptr&&tree->right==nullptr) {
			std::shared_ptr<Node<T>> node(new Node<T>(copyTree(tree->left), nullptr, tree->data));
			return node;
		}
		if (tree->left==nullptr&&tree->right==nullptr) {
			std::shared_ptr<Node<T>> node(new Node<T>(nullptr, nullptr, tree->data));
			return node;
		}
 }

	~Tree() {}


	int maxRoute(std::shared_ptr<Node<T>> cur) {
		int max = this->root == cur ? 0 : 1;
		int leftCount = 0, rightCount = 0;
		if (cur->left || cur->right) {
			if (cur->left)
				leftCount = maxRoute(cur->left);
			if (cur->right)
				rightCount = maxRoute(cur->right);
			max += leftCount > rightCount ? leftCount : rightCount;
		}
		return max;
 
	}

	int sumRoute(std::shared_ptr<Node<T>> cur) {
		int sum = 0;
		if (cur->left) {
			sum += 1 + sumRoute(cur->left);
		}
		if (cur->right) {
			sum += 1 + sumRoute(cur->right);
		}
		return sum;
	}

	void printTree(std::shared_ptr<Node<T>> cur) {
		std::cout << '(' << cur->data;
		if (cur->left || cur->right) {
			if (cur->left) {
				printTree(cur->left);
			}
			else {
				std::cout << "()";
			}
			if (cur->right) {
				printTree(cur->right);
			}
			else {
				std::cout << "()";
			}	
		}
		std::cout << ')';
	}

private:

	std::shared_ptr<Node<T>> createTree(std::string& str) {
	std::string left, right;
	if (str.size() < 3) {
		return nullptr;
	}
	if(str.size()==3){
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>();
		node->left = nullptr;
		node->right = nullptr;
		node->data = str[1];
		return node;
	}
	if (str.size() > 3) {
		int count = 0;
		int i = 2;
		do {
			if (str[i] == '(') {
				count += 1;
			}
			if (str[i] == ')') {
				count -= 1;
			}
			i++;
		} while (count);
		left = str.substr(2, i-2);
		right = str.substr(i,str.size()-1-i);
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>();
		node->left = createTree(left);
		node->right = createTree(right);
		node->data = str[1];
		return node;
	}
 
}
	//void deleteTree(std::shared_ptr<Node>);
};
#endif 
