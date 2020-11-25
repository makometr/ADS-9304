#include <iostream>
#include <memory>
#include <string>
#include <iterator>
#include <queue>
#include <algorithm>

#define invStringArg() {\
	std::cout << "ERROR: given string tree is invalid";\
	exit(EXIT_SUCCESS);\
}
int getInt(std::string::iterator& it, const std::string::iterator end) {
	int val = 0;
	bool isNegative = false;
	if (*it == '-') {
		isNegative = true;
		it++;
	}
	if (!isdigit(*it) && *it == '(')invStringArg();
	while (it != end && isdigit(*it))
		val = val * 10 + *(it++) - '0';
	if (it == end)invStringArg();
	return isNegative ? -val : val;
}
template <typename T>
struct Node {
	int data = 0;
	std::shared_ptr<Node> left, right;
	Node(T data) :data(data) {}
};
template <typename T>
using NodePtr = std::shared_ptr<Node<T>>;
template <typename T>
class BinTree {
public:
	BinTree() :head(nullptr) {}
	BinTree(const std::string::iterator begin, const std::string::iterator end) {
		auto it = begin;
		auto makeBinTree = [&it, &end](NodePtr<int> & node, auto makeBinTree) -> void {
			if (*it == ')') return;
			if (*it == '!') {
				it++;
				return;
			}
			if (*(it++) != '(' || it == end)
				invStringArg();
			node = std::make_shared<Node<int>>(getInt(it, end));
			makeBinTree(node->left, makeBinTree);
			makeBinTree(node->right, makeBinTree);
			it++;
		};
		makeBinTree(head, makeBinTree);
	}
	BinTree& operator=(const BinTree<T> & val) {
		_copy(head, val.head);
		return *this;
	}
	BinTree(const BinTree<T>& val) {
		_copy(head, val.head);
	}
	bool BinSearchCheck() {
		long min = LONG_MIN;
		bool isBinSearch = true;
		auto binCheck = [&isBinSearch, &min](const NodePtr<T> & node, auto && binCheck) {
			if (!node || !isBinSearch)
				return;
			binCheck(node->left, binCheck);
			isBinSearch &= node->data > min;
			min = node->data;
			binCheck(node->right, binCheck);
		};
		binCheck(head, binCheck);
		return isBinSearch;
	}
	bool PyramideCheck() {
		auto _pyramideCheck = [](const NodePtr<T> & node, auto && _pyramideCheck) -> bool {
			return ((node->left) ? (node->data >= node->left->data) && _pyramideCheck(node->left, _pyramideCheck) : true) \
				&& ((node->right) ? (node->data >= node->right->data) && _pyramideCheck(node->right, _pyramideCheck) : true);
		};
		return _pyramideCheck(head, _pyramideCheck);
	}
	void debug_print(){
		std::queue<NodePtr<T>> que;
		std::cout<<"Binary tree:\n|";
		que.push(head);
		que.push(nullptr);
		while(que.size()>1){
			NodePtr<T>& front = que.front();
			que.pop();
			if(!front){
				std::cout<<"\n|";
				que.push(nullptr);
				continue;
			}
			std::cout<<front->data<<' ';
			if(front->left) que.push(front->left);
			if(front->right) que.push(front->right);
		}
		std::cout<<"\n-----\n";
	}
private:
	NodePtr<T> head;
	void _copy(NodePtr<T> & dest, const NodePtr<T> & source){
		if (source) {
			dest = std::make_shared<Node<T>>(source->data);
			_copy(dest->left, source->left);
			_copy(dest->right, source->right);
		}
	};
};
int main() {
	std::string input;
	std::getline(std::cin, input);
	BinTree<int> tree(input.begin(), input.end());
	tree.debug_print();
	std::cout << "Binsearch:\t" << (tree.BinSearchCheck() ? "Yes" : "No") \
		<< "\nPyramid:\t" << (tree.PyramideCheck() ? "Yes" : "No") << '\n';
	return 0;
}