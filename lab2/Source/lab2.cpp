#include "list.h"
#include <iostream>
#include <string>
#include <variant>

int main(int argc, char *argv[])
{
	std::string str;
	char symbol;
	if(argc<2){
		std::cin >> str;
		std::cin >> symbol;
	}
	int size = str.size();
	char* arr = new char[size];
	for (int i = 0; i < size; i++) {
		arr[i] = str[i];
	}
 
	List lst(arr, size);
	lst.deleteAtom(lst.head, symbol);
	lst.print(lst.head);
 
	delete[] arr;
}
