#pragma once
#include <queue>
#include <algorithm>
#include <random>

#include "RBTree.h"

class RBTester {
public:
	RBTester(RBTree<int>& tree) :tree(tree) {}
	void insertBest();
	void insertAverage();
	void insertWorst();
private:
	RBTree<int>& tree;
};

void RBTester::insertBest() {
	tree.clear();
	std::queue<int>que;
	que.push(1<<19);
	que.push(0);
	int jmpLength = 1 << 18;
	std::ofstream f("insertBest.txt", std::fstream::out);
	while (jmpLength>0) {
		int cur = que.front();
		que.pop();
		if (cur == 0) {
			jmpLength >>= 1;
			que.push(0);
			continue;
		}
		f << tree.size() << ' ' << tree.insert(cur) << '\n';
		que.push(cur - jmpLength);
		que.push(cur + jmpLength);
	}
	while (!que.empty()) {
		int cur = que.front();
		que.pop();
		if (cur == 0)
			continue;
		else
			f << tree.size() << ' ' << tree.insert(cur) << '\n';
	}
	f << tree.size() << ' ' << tree.insert(1 << 20) << '\n';
}

void RBTester::insertAverage()
{
	tree.clear();
	std::vector<int>values;
	values.resize(1 << 20);
	for (int i = 0; i < 1 << 20; i++)
		values[i] = i+1;
	std::shuffle(values.begin(), values.end(), std::mt19937(std::random_device()()));
	std::ofstream f("insertAverage.txt", std::fstream::out);
	for (int i = 0; i < 1 << 20; i++)
		f << tree.size() << ' ' << tree.insert(values[i]) << '\n';
}

void RBTester::insertWorst() {
	tree.clear();
	std::ofstream f("insertWorst.txt", std::fstream::out);
	for (int i = 1; i <= 1<<20; i++) {
		f << tree.size() << ' ' << tree.insert(i) << '\n';
	}
}