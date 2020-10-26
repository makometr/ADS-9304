#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "tree.h"
 
bool checkString(std::string str) {
	int size = str.size();
	if (size < 3) {
		std::cerr<< "The tree has no root" <<'\n';
		return 0;
	}
	if (str[0] != '(') {
		std::cerr << "The first symbol is not correct" << '\n';
		return 0;
	}
	int counter = 1;
	for (int i = 1; i < size; i++) {
		if (str[i] == '(') {
			counter += 1;
		}
		if (str[i] == ')') {
			counter -= 1;
		}
	}
	if (counter) {
		std::cerr << "Wronq numder of brackets\n";
		return 0;
	}
	return 1;
}
 
int main() {
	std::string str1, str2;
	char value;
	std::getline(std::cin, str1);
	std::stringstream ss(str1);
 
	while (ss >> value)
	{
		str2.push_back(value);
 
		if (ss.peek() == ' ') {
			ss.ignore();
		}
	}
	if (!checkString(str2)) {
		std::cout<<"You entered wrong string"<<'\n';
		return 0;
	}
	Tree tree(str2);
	std::cout << tree.maxRoute(tree.root) << '\n';
	std::cout << tree.sumRoute(tree.root) << '\n';
	//tree.printTree(tree.root);
}
