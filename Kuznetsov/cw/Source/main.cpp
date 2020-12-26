#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

#include "RBTree.h"
#include "RBTester.h"

int main(int argc, char** argv) {
#ifdef _WIN32
	std::system("color 80");
#endif
	RBTree<int> tree;
#ifdef GRAPH
		RBTester tester(tree);
		if(argc==2 && !std::strcmp(argv[1], "worst"))
			tester.insertWorst();
		else if (argc==2 && !std::strcmp(argv[1], "average"))
			tester.insertAverage();
		else if(argc==2 && !std::strcmp(argv[1], "best"))
			tester.insertBest();
		else {
			tester.insertWorst();
			tester.insertAverage();
			tester.insertBest();
		}
		return 0;
#endif
	while (true) {
		std::string userInput;
		std::getline(std::cin, userInput);
		std::stringstream sstr(userInput);
		int value;
		while (sstr >> value)
			tree.insert(value);
#ifdef _DEBUG
		tree.outputLayers(std::cout);
#endif
#ifdef TEST
		std::ofstream file("res.txt", std::ofstream::out);
		tree.outputSorted(file);
		break;
#endif
	}
	return 0;
}