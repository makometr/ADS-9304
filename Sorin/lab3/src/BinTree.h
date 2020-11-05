#ifndef __BIN_TREE_H
#define __BIN_TREE_H

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <memory>
#include <vector>

template <typename base>
class bin_tree_node {
public:
	base Value;
	int LeftElemNum = -1;
	int RightElemNum = -1;
	bin_tree_node() = default;
	~bin_tree_node() = default;
};

template <typename base>
class bin_tree {
public:
	bin_tree() : size(0), head(nullptr) {
	}
	~bin_tree() = default;

	bin_tree(bin_tree_node<base> BTnode) : size(1) {
		head(new bin_tree_node<base>[1]);
		head[0] = BTnode;
	}

	bin_tree(bin_tree<base>& tree) {
		size = tree.size;
		head(new bin_tree_node<base>[size]);
		for (int i = 0; i < size; i++) {
			head[i] = tree.head[i];
		}
	}
	bin_tree<base>& operator=(bin_tree<base>& tree) {
		size = tree.size;
		head(new bin_tree_node<base>[size]);
		for (int i = 0; i < size; i++) {
			head[i] = tree.head[i];
		}
		return *this;
	}

	bin_tree(bin_tree<base>&& tree) {
		head = std::move(tree.head);
	}
	bin_tree<base>& operator=(bin_tree<base>&& tree) {
		head = std::move(tree.head);
		return *this;
	}

	void AddToLeftOfPos(size_t pos) {
		if (pos >= size)
			throw std::invalid_argument("Error of position");
		if (head[pos].LeftElemNum != -1)
			throw std::invalid_argument("The node is already on the left");
		else {
			head[pos].LeftElemNum = size;
			AddElem();
		}
	}

	void AddToRightOfPos(size_t pos) {
		if (pos >= size)
			throw std::invalid_argument("Error of position");
		if (head[pos].RightElemNum != -1)
			throw std::invalid_argument("The node is already on the left");
		else {
			head[pos].RightElemNum = size;
			AddElem();
		}
	}
	void ReadBT(std::stringstream& Stream) {
		if (head == nullptr)
			AddElem();
		char c = 0;
		if (!Stream.get(c))
			throw std::invalid_argument("Error while entering expression");
		if (c != '(')
			throw std::invalid_argument("Error while entering expression");
		ReadBTRec(0, Stream);
	}

	bool IsIdenticalNodes(void) {
		std::vector<base> Save;
		
		for (size_t k = 0; k < size; k++) {
			for (size_t i = 0; i < Save.size(); i++)
				if (head[k].Value == Save[i])
					return true;
			Save.push_back(head[k].Value);
		}
		return false;
	}

	void OrderLKP(void (* func)(bin_tree_node<base> BTnode), int Ind = 0) {
		if (Ind < size)
		{
			if (head[Ind].LeftElemNum != -1)
				OrderLKP(func, head[Ind].LeftElemNum);
			func(head[Ind]);
			if (head[Ind].RightElemNum != -1)
				OrderLKP(func, head[Ind].RightElemNum);
		}
		return;
	}
	static void PrintNode(bin_tree_node<base> BTnode) {
		std::cout << (char)BTnode.Value;
	}
private:
	std::shared_ptr<bin_tree_node<base>[]> head;
	size_t size;

	void AddElem(void) {
		std::shared_ptr<bin_tree_node<base>[]> tmp(new bin_tree_node<base>[size + 1]);
		for (size_t i = 0; i < size; i++) {
			tmp[i] = head[i];
		}
		head = std::move(tmp);
		size++;
	}

	void ReadBTRec(int Ind, std::stringstream& Stream) {
		int IsO = 0;
		char c = 0;

		if (!Stream.get(c))
			throw std::invalid_argument("Error while entering expression");
		if (c < 'a' || c > 'z')
			throw std::invalid_argument("Error while entering expression");
		head[Ind].Value = (base)c;
		
		if (Stream.get(c)) {
			if (c == '^')
				IsO++;
			else if (c == '(') {
				AddToLeftOfPos(Ind);
				ReadBTRec(size - 1, Stream);
				IsO++;
			}
			else
				throw std::invalid_argument("Error while entering expression");
		}
		else
			throw std::invalid_argument("Error while entering expression");

		if (Stream.get(c)) {
			if (c == '^')
				IsO++;
			else if (c == '(') {
				AddToRightOfPos(Ind);
				ReadBTRec(size - 1, Stream);
				IsO++;
			}
			else
				throw std::invalid_argument("Error while entering expression");
		}
		else
			throw std::invalid_argument("Error while entering expression");
		
		if (!Stream.get(c))
			throw std::invalid_argument("Error while entering expression");
		if (c != ')')
			throw std::invalid_argument("Error while entering expression");

		return;
	}

};


#endif // __BIN_TREE_H

