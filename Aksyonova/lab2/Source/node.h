#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <variant>
 
class Node
{
	friend class List;
	//указатель на следующий элемент списка(линеной части)
	Node* next;
	//данные, которые хранит узел(либо символ, либо указатель на другой список)
	std::variant<Node*, char> data;
public:
	Node(Node*, std::variant<Node*, char>);
	~Node();
 
};
#endif
