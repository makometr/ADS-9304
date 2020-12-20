#include "AVLTree.h"
#include "Node.h"

AVLTree::AVLTree()
{
	std::string str;

	std::cout << "Enter set of digits: ";
	std::getline(std::cin, str);
	std::istringstream iss(str);
	
	int digit;
	while (iss >> digit) {
		this->Insert(digit);
	}
}

AVLTree::~AVLTree()
{
}

// Demonstation
void AVLTree::PrintTree(std::shared_ptr<Node> node, int tab)
{
	int temp = tab;
	std::string str = "";
	while (temp != 0) {
		str += "  ";
		temp--;
	}

	if(node != nullptr) {
		std::cout << str << node->key_ << '\n';
		if (node->left_ != nullptr) {
			this->PrintTree(node->left_, tab + 1);
		}
		if (node->right_ != nullptr) {
			this->PrintTree(node->right_, tab + 1);
		}
	}
	else {
		std::cout << "Tree is empty!\n";
	}
}

void AVLTree::Demonstration(DemoState state)
{
	int input = 0;
	if (state == DemoState::InsertDemo) {
		std::cout << "\nInput key with you want to insert: ";
		std::cin >> input;

		this->Insert(input, DemoState::InsertDemo);

		std::cout << "\n ---< Tree after insert key " << input << " >--- \n\n";
		this->PrintTree(this->Front());
	}
	else if (state == DemoState::RemoveDemo) {
		std::cout << "\nInput key with you want to remove: ";
		std::cin >> input;

		this->Remove(input, DemoState::RemoveDemo);

		std::cout << "\n ---< Tree after remove key " << input << " >--- \n\n";
		this->PrintTree(this->Front());
	}
}

///////////////////////////////////////////////////////////////////////

std::shared_ptr<Node> AVLTree::Front()
{
	return this->head_;
}

std::shared_ptr<Node> AVLTree::Find(int key, DemoState state)
{
	return Node::Find(key, this->head_);
}

void AVLTree::Remove(int key, DemoState state)
{
	this->head_ = Node::Remove(key, this->head_, state);
}

void AVLTree::Insert(int key, DemoState state)
{
	this->head_ = Node::Insert(key, this->head_, state);
}





