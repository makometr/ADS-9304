#pragma once
#include "Includes.h"

class Node;

class AVLTree
{
public:
	std::shared_ptr<Node> head_ = nullptr;

	AVLTree();

	void PrintTree(int tab = 1, std::shared_ptr<Node> node = nullptr); //Сдлеать норм вывод
	int FindAll(int key);

private:
	int FindAll(int key, std::shared_ptr<Node> node);
};

