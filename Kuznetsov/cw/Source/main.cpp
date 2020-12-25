#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <memory>
#include <queue>
#include <cstdio>
#include "RBTree.h"

int main() {
#ifdef _WIN32
	std::system("color 80");
#endif
	std::cout << "\033[30;48m";
	std::ofstream fstr;
	fstr.open("res.txt");
	RBTree<int> tree;
	int tmp;
	char c = ' ';
	while (c != '\n' && c != EOF) {
		scanf(" %d%c", &tmp, &c);
		tree.insert(tmp);
	}
	tree.outputSorted(fstr);
	fstr.close();
#ifdef _DEBUG
	tree.outputLayers(std::cout);
#endif
	return 0;
}