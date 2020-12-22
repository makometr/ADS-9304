#pragma once
#include "Includes.h"

class Node;

class AVLTree
{
public:
	static AVLTree* ptr_tree_;
	
	AVLTree();
	~AVLTree();

	static AVLTree* GetTree();
	static void DeleteTree();

	static void PrintTree(std::shared_ptr<Node> node, int tab = 1); 
	void Demonstration(DemoState state);

	std::shared_ptr<Node> Front();
	std::shared_ptr<Node> Find(int key, DemoState state = DemoState::NoDemo);

	void Remove(int key, DemoState state = DemoState::NoDemo);
	void Insert(int key, DemoState state = DemoState::NoDemo);

private:
	std::shared_ptr<Node> head_ = nullptr;
	
};

