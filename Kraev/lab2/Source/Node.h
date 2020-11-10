#pragma once
#include <string>
#include <variant>
#include <vector>
#include <iterator>
#include <iostream>

class Node{
public:
	Node* next;
    
	std::vector<int> number;
	
	std::string name;

	bool isKnot;

	std::variant<Node*, std::string> value;
	
	Node(std::string &str);
	
	void print();
	
	~Node();
};
