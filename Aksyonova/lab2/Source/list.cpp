#include "list.h"
 
List::List(char* arrOfBukoff, int sizeArr) {
	head = createNode(arrOfBukoff, sizeArr, 0);
}
 
List::~List() {
	deleteNode(head);
}
 
void List::print(Node* cur) {
	if (std::holds_alternative<Node *>(cur->data)) {
		std::cout << '(';
		if (std::get<Node*>(cur->data) != nullptr) {
			print(std::get<Node*>(cur->data));
		}
		std::cout << ')';
	} else {
		std::cout << std::get<char>(cur->data);
	}
	if (cur->next != nullptr) {
		print(cur->next);
	}
}
 
Node* List::createNode(char* arrOfBukoff, int sizeArr, int index) {
	if (index < sizeArr - 1) {
		if (arrOfBukoff[index] == '(') {
			int i, count = 1;
			for (i = index + 1; i < sizeArr; i++) {
				if (arrOfBukoff[i] == '(') {
					count += 1;
				}
				if (arrOfBukoff[i] == ')') {
					count -= 1;
				}
				if (count == 0) {
					break;
				}
			}
			if (i == sizeArr - 1 || arrOfBukoff[i + 1] == ')') {
				Node* uzel = new Node(nullptr, createNode(arrOfBukoff,sizeArr, index + 1));
				return uzel;
			} else {
				Node* uzel = new Node(createNode(arrOfBukoff, sizeArr, i + 1), createNode(arrOfBukoff, sizeArr, index + 1));
				return uzel;
			}
		} else if (arrOfBukoff[index] == ')') {
			return nullptr;
		} else {
			Node* atom = new Node(createNode(arrOfBukoff, sizeArr, index + 1), arrOfBukoff[index]);
			return atom;
		}
	} else {
		return nullptr;
	}
}
 
void List::deleteAtom(Node* cur, char toDelete) {
	if (cur != nullptr) {
		bool flag = false;
		if (std::holds_alternative<Node*>(cur->data)) {
			if (std::get<Node*>(cur->data) != nullptr) {
				if (std::holds_alternative<Node*>(std::get<Node*>(cur->data)->data)) {
					deleteAtom(std::get<Node*>(cur->data), toDelete);
				} else {
					if (std::get<char>(std::get<Node*>(cur->data)->data) == toDelete) {
						Node* temp = std::get<Node*>(cur->data);
						cur->data = std::get<Node*>(cur->data)->next;
						delete temp;
						flag = true;
					} else {
						deleteAtom(std::get<Node *>(cur->data), toDelete);
					}
				}
			}
		}
		if (cur->next != nullptr) {
			if (std::holds_alternative<Node*>(cur->next->data)) {
				deleteAtom(cur->next, toDelete);
			} else {
				if (std::get<char>(cur->next->data) == toDelete) {
					Node* temp = cur->next;
					cur->next = cur->next->next;
					delete temp;
					flag = true;
				} else {
					deleteAtom(cur->next, toDelete);
				}
			}
		}
		if (flag) {
			deleteAtom(cur, toDelete);
		}
	}
}
 
void List::deleteNode(Node* cur) {
	if (cur != nullptr) {
		if (std::holds_alternative<Node*>(cur->data)) {
			deleteNode(std::get<Node*>(cur->data));
		}
		deleteNode(cur->next);
		delete cur;
	}
}
