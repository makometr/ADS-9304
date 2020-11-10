#include "list.h"
#include <iostream>
#include <string>
#include <variant>

int main(int argc, char *argv[])
{
	std::string str;
	std::string strDel;
	char symbol;
	if(argc<2){
		std::cin >> str;
		std::cin >> strDel;
	}
	int size = str.size();
	if(str[0] != '('){
		std::cerr<<"The first symbol is not correct"<<'\n';
		return 0;
	}
	int counter = 1;
	for(int i = 1; i<size; i++){
		if(str[i]=='('){
			counter+=1;
		}
		if(str[i]==')'){
			counter-=1;
		}
	}
	if(counter){
		std::cerr<<"Wronq numder of brackets\n";
		return 0;
	}
	if(strDel.size()>1){
		std::cout<<"You entered a strind. I wiil delete only first symbol"<<'\n';
	}
	symbol = strDel[0];
	char* arr = new char[size];
	for (int i = 0; i < size; i++) {
		arr[i] = str[i];
	}
 
	List lst(arr, size);
	lst.deleteAtom(lst.head, symbol);
	lst.print(lst.head);
 
	delete[] arr;
}
