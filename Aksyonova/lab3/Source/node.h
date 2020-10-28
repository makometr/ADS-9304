#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <memory>
class Node {
public:
	Node();
	Node(std::shared_ptr<Node>,std::shared_ptr<Node>,char);
private:
	std::shared_ptr<Node> left, right;
	char data;
	friend class Tree;
};
#endif
