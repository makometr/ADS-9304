#include <memory>

template <typename T>
class Node{
public:
	std::shared_ptr<Node<T>> right;
	std::shared_ptr<Node<T>> left;
	T value;
	Node(T val){
		this->value = val;
    		this->left = nullptr;
    		this->right = nullptr;
	}
	~Node(){}
};
