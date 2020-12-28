#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "AVLTree.h"
#include "Node.h"


int main() {
	
	AVLTree::GetTree();
	
	int input = 0;
	char c = 'y';
	char state_input;
	
	do {	
		std::cout << "\nWhat do you want to demonstrate? (Insert - I / Remove - R): ";
		std::cin >> state_input;

		system("cls");
		std::cout << "\n --- < Tree > ---\n";
		AVLTree::PrintTree(AVLTree::GetTree()->Front());

		if (state_input == 'I') {
			AVLTree::GetTree()->Demonstration(DemoState::InsertDemo);
		}
		else if (state_input == 'R') {
			AVLTree::GetTree()->Demonstration(DemoState::RemoveDemo);
		}
		else {
			std::cout << "\nWrong input!";
		}

		std::cout << "\nDo you want to continue (yes - y/ no - n): ";
		std::cin >> c;
		std::cout << std::endl;

	} while (c == 'y');

	AVLTree::DeleteTree();
	_CrtDumpMemoryLeaks();
	return 0;
}