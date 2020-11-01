#pragma once
#include "Node.h"
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <variant>
#include <fstream>

Node* min(std::vector<Node*> &nodes, std::vector<int> N);
void print(Node* node,  int N);
Node* createList(std::vector<Node*> &nodes, std::vector<int> N={});
void clean(Node* node);

class List{
private:
public:
	Node* firstElem;
	friend class Node;
	List(std::string text);	
	void print();
	void addElem(std::string newElem);
	void deleteElem(std::vector<int> elem);
	void deleteElem(std::string elem, Node* cur = nullptr);
	void changeName(std::vector<int> elem, std::string newName);
	void changeNumber(std::vector<int> number, std::vector<int> newNumber);
	~List();
};


