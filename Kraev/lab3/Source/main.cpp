#include "BinTree.h"
#include <string>
#include <iostream>
#include <memory>


template <typename T>
int Count(const T &val,const std::shared_ptr<Node<T>> &cur){
    int count = 0;
    if(cur->value == val)
        count++;
    if(cur->left != nullptr)
        count += Count(val,cur->left);
    if(cur->right != nullptr)
        count += Count(val, cur->right);
    return count;
}

template <typename T>
bool checkEqual(const std::shared_ptr<Node<T>> &cur, const std::shared_ptr<Node<T>> &first){
	bool eq = false,eqleft = false,eqright = false;
	if(Count(cur->value, first) > 1)
		eq = true;
	if(cur->left != nullptr)
		eqleft = checkEqual(cur->left, first);
	if(cur->right != nullptr)
		eqright = checkEqual(cur->right, first);
	return eq || eqleft || eqright;
}




int main(int argc, char* argv[]){
	if(argc == 1){
		std::cerr << "Usage: ./lab \"BinTree\"\nFor example: ./lab a(b(d)(e))(c)\n";
		exit(0);
	}
	BinTree<char> BT(argv[1]);
	//BT.printTree();
	if(checkEqual<char>(BT.first,BT.first))
		std::cout << "True\n";
	else
		std::cout << "False\n";
}


