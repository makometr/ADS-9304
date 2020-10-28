#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <string>
#include <memory>
#include "node.h"
class Tree {
public:
	Tree(std::string&);
	Tree(const Tree&);
	Tree(Tree&&);
	Tree &operator = (const Tree &);
	Tree &operator = (Tree &&);
	~Tree();
	std::shared_ptr<Node> copyTree(std::shared_ptr<Node>);
	void printTree(std::shared_ptr<Node>);
	std::shared_ptr<Node> root;
	int maxRoute(std::shared_ptr<Node>);
	int sumRoute(std::shared_ptr<Node>);
private:
	std::shared_ptr<Node> createTree(std::string&);
	//void deleteTree(std::shared_ptr<Node>);
};
#endif 
