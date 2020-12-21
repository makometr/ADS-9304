#include "AVLTree.h"
#include "Node.h"

AVLTree::AVLTree()
{
	int digit;
	std::string str;

	std::cout << "Enter set of digits: ";
	std::getline(std::cin, str);
	std::istringstream iss(str);

	while (iss >> digit) {
		this->head_ = Insert(digit, this->head_);
	}
}

void AVLTree::PrintTree(int tab, std::shared_ptr<Node> node)
{
	int temp = tab;
	std::string str = "";
	while (temp != 0) {
		str += "  ";
		temp--;
	}

	if (node == nullptr) {
		std::cout << str << this->head_->key_ << '\n';
		this->PrintTree(tab + 1, this->head_->left_);
		this->PrintTree(tab + 1, this->head_->right_);
	}
	else {
		std::cout << str << node->key_ << '\n';
		if (node->left_ != nullptr) {
			this->PrintTree(tab + 1, node->left_);
		}
		if (node->right_ != nullptr) {
			this->PrintTree(tab + 1, node->right_);
		}
	}
}

//Задание лабораторной (подсчет количества элементов с ключом К)
int AVLTree::FindAll(int key)
{
	std::shared_ptr<Node> temp;

	temp = Find(key, this->head_);

	if (temp == nullptr) {
		return 0;
	}
	else {
		return 1 + this->FindAll(key, temp->left_) + this->FindAll(key, temp->right_);
	}
}

// Перегруженная функция FindALL (приватная)
int AVLTree::FindAll(int key, std::shared_ptr<Node> node)
{
	std::shared_ptr<Node> temp;

	temp = Find(key, node);

	if (temp == nullptr) {
		return 0;
	}
	else {
		return 1 + this->FindAll(key, temp->left_) + this->FindAll(key, temp->right_);
	}
}



