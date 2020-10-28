#include "tree.h"
Tree::Tree(std::string& str) {
	root = createTree(str);
}

Tree::Tree(const Tree& tree){
	root = copyTree(tree.root);
}
Tree::Tree(Tree&& tree){
	std::swap(tree.root, root);
}
Tree& Tree::operator = (const Tree & tree){
	root = copyTree(tree.root);
	return *this;
}
Tree& Tree::operator = (Tree && tree){
	root = std::move(tree.root);
	return *this;
}
std::shared_ptr<Node> Tree::copyTree(std::shared_ptr<Node> tree){
	if (tree->left!=nullptr&&tree->right!=nullptr) {
		std::shared_ptr<Node> node(new Node(copyTree(tree->left), copyTree(tree->right), tree->data));
		return node;
	}
	if (tree->left==nullptr&&tree->right!=nullptr) {
		std::shared_ptr<Node> node(new Node(nullptr, copyTree(tree->right), tree->data));
		return node;
	}
	if (tree->left!=nullptr&&tree->right==nullptr) {
		std::shared_ptr<Node> node(new Node(copyTree(tree->left), nullptr, tree->data));
		return node;
	}
	if (tree->left==nullptr&&tree->right==nullptr) {
		std::shared_ptr<Node> node(new Node(nullptr, nullptr, tree->data));
		return node;
	}
}
Tree::~Tree() {
}
std::shared_ptr<Node> Tree::createTree(std::string& str) {
	std::string left, right;
	if (str.size() < 3) {
		return nullptr;
	}
	if(str.size()==3){
		std::shared_ptr<Node> node = std::make_shared<Node>();
		node->left = nullptr;
		node->right = nullptr;
		node->data = str[1];
		return node;
	}
	if (str.size() > 3) {
		int count = 0;
		int i = 2;
		do {
			if (str[i] == '(') {
				count += 1;
			}
			if (str[i] == ')') {
				count -= 1;
			}
			i++;
		} while (count);
		left = str.substr(2, i-2);
		right = str.substr(i,str.size()-1-i);
		std::shared_ptr<Node> node = std::make_shared<Node>();
		node->left = createTree(left);
		node->right = createTree(right);
		node->data = str[1];
		return node;
	}
 
}
 
int Tree::maxRoute(std::shared_ptr<Node> cur) {
	int max = this->root == cur ? 0 : 1;
	int leftCount = 0, rightCount = 0;
	if (cur->left || cur->right) {
		if (cur->left)
			leftCount = maxRoute(cur->left);
		if (cur->right)
			rightCount = maxRoute(cur->right);
		max += leftCount > rightCount ? leftCount : rightCount;
	}
	return max;
 
}
 
int Tree::sumRoute(std::shared_ptr<Node> cur) {
	int sum = 0;
	if (cur->left) {
		sum += 1 + sumRoute(cur->left);
	}
	if (cur->right) {
		sum += 1 + sumRoute(cur->right);
	}
	return sum;
}
 
void Tree::printTree(std::shared_ptr<Node> cur) {
	std::cout << '(' << cur->data;
	if (cur->left || cur->right) {
		if (cur->left) {
			printTree(cur->left);
		}
		else {
			std::cout << "()";
		}
		if (cur->right) {
			printTree(cur->right);
		}
		else {
			std::cout << "()";
		}	
	}
	std::cout << ')';
}
