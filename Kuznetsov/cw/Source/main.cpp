#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

#include "RBTree.h"
#include "RBTester.h"

int main(int argc, char** argv) {
#ifdef _WIN32
	std::system("color 80");
#endif
	RBTree<int> tree;
	if (argc == 2 && !std::strcmp(argv[1], "TEST")) {
		RBTester tester(tree);
		tester.insertWorst();
		tester.insertAverage();
		tester.insertBest();
		return 0;
	}
	while (true) {
		std::string userInput;
		std::getline(std::cin, userInput);
		std::stringstream sstr(userInput);
		int value;
		while (sstr >> value)
			tree.insert(value);
		tree.outputLayers(std::cout);
	}
	return 0;
}