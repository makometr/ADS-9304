#include <iostream>
#include <memory>
#include <string>
#include <iterator>
#include <queue>
#include <algorithm>

struct Node;
using NodePtr = std::shared_ptr<Node>;
#define invStringArg() {\
	std::cout << "ERROR: given string tree is invalid";\
	exit(EXIT_SUCCESS);\
}

struct Node {
	int data = 0;
	NodePtr left, right;
	Node(int data) :data(data) {}
};
int getInt(std::string::iterator& it, const std::string::iterator end) {
	int val = 0;
	bool isNegative = false;
	if (*it == '-') {
		isNegative = true;
		it++;
	}
	if(!isdigit(*it) && *it =='(')invStringArg();
	while (it!=end && isdigit(*it))
		val = val * 10 + *(it++) - '0';
	if (it == end)invStringArg();
	return isNegative ? -val : val;
}
bool BinSearchCheck(const NodePtr& node) {
	int min = INT_MIN;
	bool isBinSearch = true;
	auto binCheck = [&](const NodePtr & node, auto && binCheck) {
		if (!node || !isBinSearch)
			return;
		binCheck(node->left, binCheck);
		isBinSearch &= node->data > min;
		min = node->data;
		binCheck(node->right, binCheck);
	};
	binCheck(node, binCheck);
	return isBinSearch;
}
bool PyramideCheck(const NodePtr &node) {
	return ((node->left) ? (node->data >= node->left->data) && PyramideCheck(node->left) :true) \
		&& ((node->right) ? (node->data >= node->right->data) && PyramideCheck(node->right) :true);
}

int main() {
	NodePtr tree;
	{std::string input;
	std::getline(std::cin, input);
	std::string::iterator it = input.begin(), end = input.end();
	auto makeBinTree = [&](NodePtr& node, auto makeBinTree) {
		if (*it == ')') return;
		if (*it == '!') {
			it++;
			return;
		}
		if (*(it++) != '(' || it == end)invStringArg();
		node = std::make_shared<Node>(getInt(it, end));
		makeBinTree(node->left, makeBinTree);
		makeBinTree(node->right, makeBinTree);
		it++;
	};
	makeBinTree(tree, makeBinTree);}
	std::cout << "Binsearch:\t" << (BinSearchCheck(tree) ? "Yes" : "No") \
		<< "\nPyramid:\t" << (PyramideCheck(tree) ? "Yes" : "No") << '\n';
	return 0;
}