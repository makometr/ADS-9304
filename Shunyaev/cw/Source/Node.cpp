#include "Node.h"
#include "AVLTree.h"

//Методы класса Node
Node::Node(int key, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
{
	this->key_ = key;
	this->height_ = 1;
	this->counter_ = 1;
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

int Node::GetCounter()
{
	return this->counter_;
}

int Node::BalanceFactor(DemoState state)
{
	int temp = (this->right_->GetHeight()) - (this->left_->GetHeight());

	if (state != DemoState::NoDemo) {
		std::cout << "\n  Balance factor of node " << this->key_ << " = " << temp << '\n';
	}

	return temp;
}

void Node::AdaptHeight(DemoState state)
{
	unsigned char left_height = this->left_->GetHeight();
	unsigned char right_height = this->right_->GetHeight();

	this->height_ = (left_height > right_height ? left_height : right_height) + 1;
	
	if (state != DemoState::NoDemo) {
		std::cout << "  Height was adapted - " << (int) this->height_;
	}
}

//////////////////////////////////////////////////////////

//Удаление
std::shared_ptr<Node> Node::Remove(int key, std::shared_ptr<Node> head, DemoState state)
{
	if (state == DemoState::InsertDemo) {
		std::cout << "\nStart removing node " << key;
	}

	if (head == nullptr) {
		if (state == DemoState::RemoveDemo) {
			std::cout << "\nThere is no such key in the tree!\n";
		}

		return nullptr;
	}

	if (key < head->key_) {
		if (state == DemoState::RemoveDemo) {
			std::cout << "\n " << key << " < " << head->key_ << " - search in left subtree\n";
		}

		head->left_ = Node::Remove(key, head->left_, state);
	}
	else if (key > head->key_) {
		if (state == DemoState::RemoveDemo) {
			std::cout << "\n " << key << " > " << head->key_ << " - search in right subtree\n";
		}

		head->right_ = Node::Remove(key, head->right_, state);
	}
	else {
		if (state == DemoState::RemoveDemo) {
			std::cout << "\nElement with key " << key << " was found!\n";
			std::cout << " Counter Decreased!\n";
			std::cout << " If counter = 0, then node will be delete\n";
			std::cout << " If counter > 0, then it mean that there are more then one element with key " << key << "\n";
		}

		head->counter_--;

		if (state == DemoState::RemoveDemo) {
			std::cout << " Counter = " << head->counter_ << "\n";
		}

		if (head->counter_ == 0) {

			if (state == DemoState::RemoveDemo) {
				std::cout << "\n Temp_left = left subtree of node";
				std::cout << "\n Temp_right = right subtree of node";
				std::cout << "\n Node is removed!";
			}

			std::shared_ptr<Node> temp_left = head->left_;
			std::shared_ptr<Node> temp_right = head->right_;
		
			head.reset();

			if (temp_right == nullptr) {
				if (state == DemoState::RemoveDemo) {
					std::cout << "\n\n Temp_right is empty, so temp_left puts on the node's place\n";
				}

				return temp_left;
			}
			else {
				if (state == DemoState::RemoveDemo) {
					std::cout << "\n\n Temp_right isn't empty, then find min key in right subtree and save it in variable \"min\": ";
					std::cout << "\n  Finding min in right subtree...";
					std::cout << "\n   If node has left subtree, then find min in left subtree";
					std::cout << "\n   Else return node\n";
				}
				std::shared_ptr<Node> min = Node::FindMin(temp_right, state);

				if (state == DemoState::RemoveDemo) {
					std::cout << "\n  Right subtree of min = temp_right without min element";
					std::cout << "\n  Left subtree of min = temp_left\n";
				}
				min->right_ = Node::RemoveMin(temp_right, state);
				min->left_ = temp_left;

				return Node::NodeBalancing(min, state);
			}
		}
	}
		
	return Node::NodeBalancing(head, state);
}

std::shared_ptr<Node> Node::FindMin(std::shared_ptr<Node> node, DemoState state)
{
	if (state == DemoState::RemoveDemo) {
		if (node->left_ != nullptr) {
			std::cout << "\n    Node with key " << node->key_ <<" has left subtree";
		}
		else {
			std::cout << "\n    Node with key " << node->key_ << " does not have left subtree\n";
		}
	}
	return node->left_ ? Node::FindMin(node->left_, state) : node;
}

std::shared_ptr<Node> Node::RemoveMin(std::shared_ptr<Node> node, DemoState state)
{
	if (state == DemoState::RemoveDemo) {
		std::cout << "\n  Removing min in right subtree...";
		if (node->left_ == nullptr) {
			std::cout << "\n    Left subtree of node with key " << node->key_ << " is empty, so right subtree of this node puts on node's place\n";
		}
		else {
			std::cout << "\n    Left subtree of node with key " << node->key_ << " isn't empty, so removing min in left subtree";
		}
	}

	if (node->left_ == nullptr) {
		return node->right_;
	}
	node->left_ = Node::RemoveMin(node->left_, state);
	return Node::NodeBalancing(node, state);
}

//Вставка 
std::shared_ptr<Node> Node::Insert(int key, std::shared_ptr<Node> head, DemoState state)
{
	if (state == DemoState::InsertDemo) {
		std::cout << "\nStart inserting node " << key;
	}

	if (head == nullptr) {
		if (state == DemoState::InsertDemo) {
			std::cout << "\n Element with key "<< key << " was created!\n";
		}
		return Node::NodeBalancing(std::make_shared<Node>(key), state);
	}
	else if (key < head->key_) {

		if (state == DemoState::InsertDemo) {
			std::cout << "\n " << key << " < " << head->key_ << " - insert in left subtree\n";
		}

		head->left_ = Node::Insert(key, head->left_, state);
	}
	else if (key > head->key_) {
		if (state == DemoState::InsertDemo) {
			std::cout << "\n " << key << " > " << head->key_ << " - insert in right subtree\n";
		}

		head->right_ = Node::Insert(key, head->right_, state);
	}
	else {
		if (state == DemoState::InsertDemo) {
			std::cout << "\n Element with key " << key << " has already exist! So counter was increased\n";
		}
		head->counter_++;
	}

	return Node::NodeBalancing(head, state);
}

//Поиск
std::shared_ptr<Node> Node::Find(int key, std::shared_ptr<Node> head, DemoState state)
{
	if (head == nullptr) {
		return nullptr;
	}
	else if (key < head->key_) {
		return Node::Find(key, head->left_, state);
	}
	else if (key > head->key_){
		return Node::Find(key, head->right_, state);
	}
	else {
		return head;
	}
}


//////////////////////////////////////////////////////////

//Вспомогательные методы 

std::shared_ptr<Node> Node::RotateRight(std::shared_ptr<Node> node, DemoState state)
{
	if (state != DemoState::NoDemo) {
		std::cout << "\n  Start rotate right node " << node->key_<< ":";
		std::cout << "\n   Temp = left subtree of node " << node->key_;
		std::cout << "\n   Left subtree of node = right subtree of temp";
		std::cout << "\n   Right subtree of temp = node";
	}

	std::shared_ptr<Node> temp = node->left_;
	node->left_ = temp->right_;
	temp->right_ = node;

	if (state != DemoState::NoDemo) {
		std::cout << "\n ";
	}
	node->AdaptHeight(state);
		
	if (state != DemoState::NoDemo) {
		std::cout << "\n ";
	}
	temp->AdaptHeight(state);
	
	if (state != DemoState::NoDemo) {
		std::cout << "\n";
	}

	return temp;
}

std::shared_ptr<Node> Node::RotateLeft(std::shared_ptr<Node> node, DemoState state)
{
	if (state != DemoState::NoDemo) {
		std::cout << "\n  Start rotate left node " << node->key_ << ":";
		std::cout << "\n   Temp = right subtree of node " << node->key_;
		std::cout << "\n   Right subtree of node = left subtree of temp";
		std::cout << "\n   Left subtree of temp = node";
	}

	std::shared_ptr<Node> temp = node->right_;
	node->right_ = temp->left_;
	temp->left_ = node;

	if (state != DemoState::NoDemo) {
		std::cout << "\n ";
	}
	node->AdaptHeight(state);

	if (state != DemoState::NoDemo) {
		std::cout << "\n ";
	}
	temp->AdaptHeight(state);

	if (state != DemoState::NoDemo) {
		std::cout << "\n";
	}

	return temp;
}

std::shared_ptr<Node> Node::NodeBalancing(std::shared_ptr<Node> node, DemoState state)
{
	if (state != DemoState::NoDemo) {
		std::cout << "\n ---< Tree before balancing node with key " << node->key_ << " >--- \n\n";
		AVLTree::PrintTree(AVLTree::GetTree()->Front());
		std::cout << "\n Start balansing node with key " << node->key_ << "\n";
	}

	node->AdaptHeight(state);
	
	int b_factor = node->BalanceFactor(state);

	if (state != DemoState::NoDemo) {
		std::cout << "   If balance factor = 2, then check balance factor of right subtree";
		std::cout << "\n   If balance factor = -2, then check balance factor of left subtree";
		std::cout << "\n   If balance factor = (-1 or 1 or 0), then tree is balanced\n";
	}

	if (b_factor == 2)
	{
		int b_factor_right_tree = node->right_->BalanceFactor(state);

		if (state != DemoState::NoDemo) {
			std::cout << "   Check balance factor of right subtree";
			std::cout << "\n   If balance factor < 0, then DO ROTATE RIGHT OF RIGHT SUBTREE and after that DO ROTATE LEFT OF CURRENT TREE ";
			std::cout << "\n   If balance factor >= 0, then DO ROTATE LEFT OF CURRENT TREE \n";
		}

		if (b_factor_right_tree < 0) {
			node->right_ = Node::RotateRight(node->right_, state);
		}
		return Node::RotateLeft(node, state);
	}
	else if (b_factor == -2)
	{
		int b_factor_left_tree = node->left_->BalanceFactor(state);

		if (state != DemoState::NoDemo) {
			std::cout << "   Check balance factor of right subtree";
			std::cout << "\n   If balance factor > 0, then DO ROTATE LEFT OF LEFT SUBTREE and, after that, DO ROTATE RIGHT OF CURRENT TREE ";
			std::cout << "\n   If balance factor <= 0, then DO ROTATE RIGHT OF CURRENT TREE \n";
		}

		if (b_factor_left_tree > 0) {
			node->left_ = Node::RotateLeft(node->left_, state);
		}
		return Node::RotateRight(node, state);
	}

	if (state != DemoState::NoDemo) {
		std::cout << "\n ---------------------------------------- \n";
	}

	return node;
}
