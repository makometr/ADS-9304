#include "AVLTree.h"
#include "Node.h"

int main() {
	char c = 'y';
	int input = 0;
	AVLTree tree;
	
	std::cout << "\nTree from input\n";
	tree.PrintTree();
	std::cout << std::endl;

	while (c == 'y') 
	{	
		std::cout << "Input key wich you want to found: ";
		std::cin >> input;

		std::cout << "\nThere are " << tree.FindAll(input) << " elements with key " << input << '\n';
		std::cout << std::endl;

		tree.head_ = Insert(input, tree.head_);

		std::cout << "\nTree after edit\n";
		tree.PrintTree();

		std::cout << "\nDo you want to continue (yes - y/ no - n): ";
		std::cin >> c;
		std::cout << std::endl;
	}
	
	return 0;
}