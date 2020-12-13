#pragma once
#include "Includes.h"

class Node
{
	friend class AVLTree;
	friend std::shared_ptr<Node> RotateRight(std::shared_ptr<Node> node);
	friend std::shared_ptr<Node> RotateLeft(std::shared_ptr<Node> node);
	friend std::shared_ptr<Node> NodeBalancing(std::shared_ptr<Node> node);
	
	friend std::shared_ptr<Node> Remove(int key, std::shared_ptr<Node> node);
	friend std::shared_ptr<Node> Insert(int key, std::shared_ptr<Node> head);
	friend std::shared_ptr<Node> Find(int key, std::shared_ptr<Node> head);

	friend std::shared_ptr<Node> FindMin(std::shared_ptr<Node> node);
	friend std::shared_ptr<Node> RemoveMin(std::shared_ptr<Node> node);

public:
	Node(int key, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr);

	unsigned char GetHeight();
	int GetKey();
	int BalanceFactor();
	void AdaptHeight();

private:
	unsigned char height_;
	int key_;
	std::shared_ptr<Node> left_;
	std::shared_ptr<Node> right_;
};

