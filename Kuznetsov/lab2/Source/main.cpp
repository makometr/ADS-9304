#include <iostream>
#include <variant>
#include <string>
#include <iterator>
#include <memory>
#include <vector>
#include <stdexcept>


struct Node {
	std::shared_ptr<Node> next {nullptr};
	std::variant<std::shared_ptr<Node>, char> val;
};
using NodePtr = std::shared_ptr<Node>;

void getList(NodePtr node, std::string::iterator it, std::string::iterator end) {
	unsigned v_capacity = 10;
	std::vector<NodePtr> levels(v_capacity, nullptr);
	int depth = 1;
	if (*it != '(')
		throw std::invalid_argument("ERROR: given list is invalid (it has to start by '('");
	it++;
	levels[0] = node;

	auto connect = [&levels, &depth](NodePtr cur) {
		if (levels[depth]) //if not first at this level
			levels[depth]->next = cur;
		else //if first at this level
			levels[depth - 1]->val = cur;
		levels[depth] = cur;
	};

	while (it != end) {
		if(depth<=0)
			throw std::invalid_argument("ERROR: given list is invalid (there are more ')' than '('");
		switch (*it) {
		case '\n':
			if (depth)
				throw std::invalid_argument("ERROR: given list is invalid (there are more '(' than ')'");
			return;
		case '(':
			{
				if (depth - 1 == v_capacity) {
					v_capacity << 1;
					levels.resize(v_capacity, nullptr);
				}
				NodePtr cur = std::make_shared<Node>();
				connect(cur);
				depth++;
			}
			break;
		case ')':
			depth--;
			break;
		default:
			{
				NodePtr cur = std::make_shared<Node>();
				cur->val = *it;
				connect(cur);
			}
		} //switch
		it++;
	} //while
}

std::ostream& operator<<(std::ostream& out, const NodePtr &list) {
	if (!list)
		return out <<')';
	if (std::holds_alternative<NodePtr>(list->val))
		out << '(' << std::get<NodePtr>(list->val);
	else
		out << std::get<char>(list->val);
	return out << list->next;
}

void changeAllEntries(NodePtr node, char a, char b) {
	if (node) {
		if (std::holds_alternative<NodePtr>(node->val))
			changeAllEntries(std::get<NodePtr>(node->val), a, b);
		else if (std::get<char>(node->val) == a)
			node->val = b;
		changeAllEntries(node->next, a, b);
	}
}

int main() {
	std::string input;
	std::getline(std::cin, input);
	char a, b;
	std::cin >> a >> b;
	NodePtr list = std::make_shared<Node>();
	getList(list, input.begin(), input.end());
	changeAllEntries(list, a, b);
	std::cout<<'('<<list;
	return 0;
}