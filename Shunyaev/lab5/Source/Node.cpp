#include "Node.h"
//Методы класса Node
Node::Node(int key, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
{
	this->key_ = key;
	this->height_ = 1;
	this->left_ = left;
	this->right_ = right;
}

unsigned char Node::GetHeight()
{
	return this ? this->height_ : 0;
}

int Node::GetKey()
{
	return this->key_;
}

int Node::BalanceFactor()
{
	return (this->right_->GetHeight()) - (this->left_->GetHeight());
}

void Node::AdaptHeight()
{
	unsigned char left_height = this->left_->GetHeight();
	unsigned char right_height = this->right_->GetHeight();

	this->height_ = (left_height > right_height ? left_height : right_height) + 1;
}

//////////////////////////////////////////////////////////

//Удаление
std::shared_ptr<Node> Remove(int key, std::shared_ptr<Node> node)
{
	if (node == nullptr) {
		return nullptr;
	}

	if (key < node->key_) {
		node->left_ = Remove(key, node->left_);
	}
	else if (key > node->key_) {
		node->right_ = Remove(key, node->right_);
	}
	else {
		std::shared_ptr<Node> temp_left = node->left_;
		std::shared_ptr<Node> temp_right = node->right_;
		
		node.reset();

		if (temp_right == nullptr) {
			return temp_left;
		}
		else {
			std::shared_ptr<Node> min = FindMin(temp_right);

			min->right_ = RemoveMin(temp_right);
			min->left_ = temp_left;

			return NodeBalancing(min);
		}
	}

	return NodeBalancing(node);
}

std::shared_ptr<Node> FindMin(std::shared_ptr<Node> node)
{
	return node->left_ ? FindMin(node) : node;
}

std::shared_ptr<Node> RemoveMin(std::shared_ptr<Node> node)
{
	if (node->left_ == nullptr) {
		return node->right_;
	}
	node->left_ = RemoveMin(node->left_);
	return NodeBalancing(node);
}

//Вставка 
std::shared_ptr<Node> Insert(int key, std::shared_ptr<Node> head)
{
	if (head == nullptr) {
		return std::make_shared<Node>(key);
	}
	else if (key < head->key_) {
		head->left_ = Insert(key, head->left_);
	}
	else {
		head->right_ = Insert(key, head->right_);
	}

	return NodeBalancing(head);
}

//Поиск
std::shared_ptr<Node> Find(int key, std::shared_ptr<Node> head)
{
	if (head == nullptr) {
		return nullptr;
	}
	else if (key < head->key_) {
		return Find(key, head->left_);
	}
	else if (key > head->key_){
		return Find(key, head->right_);
	}
	else {
		return head;
	}
}


//////////////////////////////////////////////////////////

//Дружественные вспомогательные функции 

std::shared_ptr<Node> RotateRight(std::shared_ptr<Node> node)
{
	std::shared_ptr<Node> temp = node->left_;
	node->left_ = temp->right_;
	temp->right_ = node;

	node->AdaptHeight();
	temp->AdaptHeight();

	return temp;
}

std::shared_ptr<Node> RotateLeft(std::shared_ptr<Node> node)
{
	std::shared_ptr<Node> temp = node->right_;
	node->right_ = temp->left_;
	temp->left_ = node;

	node->AdaptHeight();
	temp->AdaptHeight();

	return temp;
}

std::shared_ptr<Node> NodeBalancing(std::shared_ptr<Node> node)
{
	node->AdaptHeight();
	
	if (node->BalanceFactor() == 2) 
	{
		if (node->right_->BalanceFactor() < 0) {
			node->right_ = RotateRight(node->right_);
		}
		return RotateLeft(node);
	}
	else if (node->BalanceFactor() == -2) 
	{
		if (node->left_->BalanceFactor() > 0) {
			node->left_ = RotateLeft(node->left_);
		}
		return RotateRight(node);
	}

	return node;
}
