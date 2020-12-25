#pragma once
#include <memory>
#include <initializer_list>
#include <queue>
#include <ostream>
#include <fstream>

/*<--------------------------[ Declaration ]---------------------------->*/

enum RBColor {
	RED,
	BLACK
};

template <typename T>
struct RBNode;

template <typename T>
using RBNodeSptr = std::shared_ptr<RBNode<T>>;

template <typename T>
using RBNodeWptr = std::weak_ptr<RBNode<T>>;

template <typename T>
struct RBNode {
	RBNode() = default;
	RBNode(T data, RBColor color, RBNodeSptr<T> left = nullptr, RBNodeSptr<T> right = nullptr) :
		data(data), color(color), left(left), right(right) {}
	RBNodeWptr<T> parent;
	RBNodeSptr<T> left, right;
	T data = NULL;
	RBColor color = RBColor::BLACK;
};

template <typename T>
class RBTree {
public:
	RBTree() = default;
	RBTree(const std::initializer_list<T>& list);
	size_t size();
	void insert(T value);
	void outputSorted(std::ostream& out);
	void outputLayers(std::ostream& out);
private:
	void RRight(RBNodeSptr<T> node);
	void RLeft(RBNodeSptr<T> node);
	void insert_1(RBNodeSptr<T> node);
	void insert_2(RBNodeSptr<T> node);
	RBNodeSptr<T> root = nullptr;
	size_t treeSize = 0;
};

/*<--------------------------[ Definition ]---------------------------->*/

template <typename T>
RBNodeSptr<T> grandParent(RBNodeSptr<T> node) {
	if (node && !node->parent.expired())
		return ((node->parent).lock()->parent).lock();
	return nullptr;
}

template <typename T>
RBNodeSptr<T> uncle(RBNodeSptr<T> node) {
	RBNodeSptr<T> gp = grandParent(node);
	return !gp ? nullptr : (((node->parent).lock() == gp->left) ? gp->right : gp->left);
}

template <typename T>
void RBTree<T>::RLeft(RBNodeSptr<T> node) {
	RBNodeSptr<T> pivot = node->right;
	pivot->parent = node->parent;
	if (pivot->parent.expired())
		root = pivot;
	if (!(node->parent.expired())) {
		if ((node->parent.lock())->left == node)
			(node->parent.lock())->left = pivot;
		else
			(node->parent.lock())->right = pivot;
	}
	node->right = pivot->left;
	if (pivot->left)
		pivot->left->parent = node;
	node->parent = pivot;
	pivot->left = node;
}

template <typename T>
void RBTree<T>::RRight(RBNodeSptr<T> node) {
	RBNodeSptr<T> pivot = node->left;
	pivot->parent = node->parent;
	if (pivot->parent.expired())
		root = pivot;
	if (!(node->parent.expired())) {
		if ((node->parent.lock())->left == node)
			(node->parent.lock())->left = pivot;
		else
			(node->parent.lock())->right = pivot;
	}
	node->left = pivot->right;
	if (pivot->right)
		pivot->right->parent = node;
	node->parent = pivot;
	pivot->right = node;
}

template <typename T>
RBTree<T>::RBTree(const std::initializer_list<T> & list) {
	for (const auto& i : list)
		insert(i);
}

template <typename T>
size_t RBTree<T>::size()
{
	return treeSize;
}

template <typename T>
void RBTree<T>::insert_1(RBNodeSptr<T> node) {
	if (node->parent.expired())
		node->color = RBColor::BLACK;
	else {
		if (node->parent.lock()->color == RBColor::BLACK)
			return;
		insert_2(node);
	}
}

template <typename T>
void RBTree<T>::insert_2(RBNodeSptr<T> node) {
	RBNodeSptr<T> U = uncle(node);
	if (U && U->color == RBColor::RED) {
		node->parent.lock()->color = RBColor::BLACK;
		U->color = RBColor::BLACK;
		RBNodeSptr<T> G = grandParent(node);
		G->color = RBColor::RED;
		insert_1(G);
	}
	else {
		RBNodeSptr<T> G = grandParent(node);
		if ((node == node->parent.lock()->right) && (node->parent.lock() == G->left)) {
			RLeft(node->parent.lock());
			node = node->left;
		}
		else if ((node == node->parent.lock()->left) && (node->parent.lock() == G->right)) {
			RRight(node->parent.lock());
			node = node->right;
		}
		G = grandParent(node);
		node->parent.lock()->color = RBColor::BLACK;
		G->color = RBColor::RED;
		if ((node == node->parent.lock()->left) && (node->parent.lock() == G->left))
			RRight(G);
		else
			RLeft(G);
	}
}

template <typename T>
void RBTree<T>::insert(T value) {
	RBNodeSptr<T> node = std::make_shared<RBNode<T>>(value, RBColor::RED);
	treeSize++;
	if (treeSize == 1)
		root = node;
	else {
		RBNodeSptr<T> it = root, father = nullptr;
		while (it) {
			father = it;
			it = (it->data < node->data) ? it->right : it->left;
		}
		node->parent = father;
		if (father->data < node->data)
			father->right = node;
		else
			father->left = node;
	}
	insert_1(node);
}

template <typename T>
void RBTree<T>::outputSorted(std::ostream & out) {
	auto pushToOut = [&out](const RBNodeSptr<T> & node, auto && pushToOut) {
		if (!node)
			return;
		pushToOut(node->left, pushToOut);
		out << node->data << ' ';
		pushToOut(node->right, pushToOut);
	};
	pushToOut(root, pushToOut);
	out << '\n';
}

template <typename T>
void RBTree<T>::outputLayers(std::ostream & out) {
	auto showTree = [&out](RBNodeSptr<int> root, auto && showTree, int p = 0, int s = 0) {
		auto showLine = [&out](const char* c, int p, int s) {
			for (int i = 0; i < p; i++) {
				out << (s & 1 ? "|  " : "   ");
				s /= 2;
			}
			out<< c;
		};
		if (!root) return;
		out << (root->color==RBColor::RED?"\033[31m":"")<<root->data << "\033[30m\n";
		if (root->left) {
			showLine("|\n", p, s); 
			showLine("L: ", p, s);
			showTree(root->left, showTree, p + 1, s + ((root->right == NULL ? 0 : 1) << p));
		}
		if (root->right) {
			showLine("|\n", p, s); 
			showLine("R: ", p, s);
			showTree(root->right, showTree, p + 1, s);
		}
	};
	showTree(root, showTree);
}