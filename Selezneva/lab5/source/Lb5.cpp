#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>


class Node {
public:
	Node(int k) {
		height = k;
	}
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
	int height;
	int key = 0;
};

class AVL_Tree {
public:
	AVL_Tree(std::vector<int> v) {
		Head = this->create_AVL(v, 0);
	}
	void print_avl() {
		print_node(this->Head);
	}
	void writing() {
		std::vector<int> vec;
		vec = LKP(this->Head, vec);
		
		std::ofstream avl("AVL.txt");
		for (auto i : vec) {
			avl << i << ' ';
		}
		avl.close(); 
	}
	
private:
	std::shared_ptr<Node> Head;
	std::vector<int> LKP(std::shared_ptr<Node> ptr, std::vector<int> vec) {
		if (ptr != nullptr) {
			vec = LKP(ptr->left, vec);
			vec.push_back(ptr->key);
			vec = LKP(ptr->right, vec);
		}
		return vec;
	}
	void print_node(std::shared_ptr<Node> ptr, int i = 0) {
		if (ptr != nullptr) {
			if (ptr->right) {
				print_node(ptr->right, i + 4);
			}
			if (i) {
				std::cout << std::setw(i) << ' ';
			}
			if (ptr->right) {
				std::cout << " /\n" << std::setw(i) << ' ';
			}
			std::cout << ptr->key << "\n ";
			if (ptr->left) {
				std::cout << std::setw(i) << ' ' << " \\\n";
				print_node(ptr->left, i + 4);
			}
		}
	}
	std::shared_ptr<Node> create_AVL(std::vector<int> v, int h) {
		if (v.size() == 1) {
			std::shared_ptr<Node> node = std::make_shared<Node>(h);
			node->left = nullptr;
			node->right = nullptr;
			node->key = v[0];
			return node;
		}
		else if (v.empty()) {
			return nullptr;
		}
		else {
			size_t i = v.size() / 2;
			std::vector<int> v_left;
			std::vector<int> v_right;
			for (size_t z = 0; z < i; ++z) {
				v_left.push_back(v.at(z));
			}
			for (size_t z = i+1 ; z < v.size(); ++z) {
				v_right.push_back(v.at(z));
			}
			std::shared_ptr<Node> node = std::make_shared<Node>(h);
			node->left = create_AVL(v_left,h+1);
			node->right = create_AVL(v_right,h+1);
			node->key = v[i];
			return node;
		}
	}
};

typedef int elem;

bool isCorrect(const std::string str) {
	size_t i = 0;
	if (str.at(0) == '-' && i != str.size() - 1) {
		++i;
	}
	while (i < str.size()) {
		if (isdigit(str.at(i))) {
			++i;
		}
		else {
			return false;
		}
	}
	return true;
}

int main() {
	std::vector<elem> out_1;
	std::string x;
	int i = 0;
	do {
		std::cin >> x;
		if (isCorrect(x)) {
			if (x.at(0) == '-') {
				std::string x_1 = x.substr(1, x.size() - 1);
				out_1.push_back(-atoi(x_1.c_str()));
			}
			else {
				out_1.push_back(atoi(x.c_str()));
			}
			i++;
		}
	} while (getchar() != '\n');

	if (!out_1.empty()) {
		std::sort(out_1.begin(), out_1.end());
		AVL_Tree tree(out_1);
		tree.print_avl();
		tree.writing();
	}
	return 0; 
}