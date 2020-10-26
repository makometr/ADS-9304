#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <memory>
class Node {
public:
	Node();
private:
	std::shared_ptr<Node> left, right;
	char data;
	friend class Tree;
};
#endif
