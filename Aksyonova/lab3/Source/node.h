#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <memory>
template <typename T>
class Node {
public:

	Node(){}

	Node(std::shared_ptr<Node<T>> left,std::shared_ptr<Node<T>> right, T data) :left(left), right(right), data(data){}
	std::shared_ptr<Node<T>> left, right;
	T data;
};
#endif
