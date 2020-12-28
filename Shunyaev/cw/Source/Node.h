#pragma once
#include "Includes.h"


class Node
{
	friend class AVLTree;

public:
	Node(int key, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr);

	unsigned char GetHeight();
	int GetKey();
	int GetCounter();
	int BalanceFactor(DemoState state = DemoState::NoDemo);
	void AdaptHeight(DemoState state = DemoState::NoDemo);
	
	static std::shared_ptr<Node> NodeBalancing(std::shared_ptr<Node> node, DemoState state = DemoState::NoDemo);
	static std::shared_ptr<Node> Remove(int key, std::shared_ptr<Node> head, DemoState state = DemoState::NoDemo);
	static std::shared_ptr<Node> Insert(int key, std::shared_ptr<Node> head, DemoState state = DemoState::NoDemo);
	static std::shared_ptr<Node> Find(int key, std::shared_ptr<Node> head, DemoState state = DemoState::NoDemo);

private:
	unsigned char height_;
	int key_;
	int counter_;
	std::shared_ptr<Node> left_;
	std::shared_ptr<Node> right_;
	
	static std::shared_ptr<Node> RotateRight(std::shared_ptr<Node> node, DemoState state = DemoState::NoDemo);
	static std::shared_ptr<Node> RotateLeft(std::shared_ptr<Node> node, DemoState state = DemoState::NoDemo);
	static std::shared_ptr<Node> FindMin(std::shared_ptr<Node> node, DemoState state = DemoState::NoDemo);
	static std::shared_ptr<Node> RemoveMin(std::shared_ptr<Node> node, DemoState state = DemoState::NoDemo);
};

