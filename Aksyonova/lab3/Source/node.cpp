#include "node.h"
Node::Node(){}
Node::Node(std::shared_ptr<Node> left,std::shared_ptr<Node> right, char data) :left(left), right(right), data(data){}
