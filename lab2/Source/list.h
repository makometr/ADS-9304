#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <variant>
#include "node.h"
class List
{
	Node* createNode(char*, int, int);
	void deleteNode(Node *);
 
public:
	Node* head;
	List(char*, int);
	~List();
	void print(Node*);
	void deleteAtom(Node*, char);
 
};
#endif
