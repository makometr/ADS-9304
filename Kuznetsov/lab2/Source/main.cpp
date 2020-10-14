#include <iostream>
#include <variant>
#include <string>
#include <iterator>
#include <memory>
#include <vector>
#include <sstream>

struct Node {
	std::shared_ptr<Node> next {nullptr};
	std::variant<std::shared_ptr<Node>, char> val;
};
using NodePtr = std::shared_ptr<Node>;
#define NewNode std::make_shared<Node>

void getList(NodePtr &node, const std::string::iterator begin, const std::string::iterator end) {
	unsigned v_capacity = 10;
	std::vector<NodePtr> levels(v_capacity, nullptr);
	int depth = 1;
	auto it = begin;
	if (*it != '('){
		std::cout << "ERROR: given string list is invalid (it has to start with '(' )\n" \
						"string value = [" << std::move(std::string(begin, end)) << "]";
		exit(EXIT_FAILURE);
	}
	it++;
	levels[0] = node;

	auto connect = [&levels, &depth](const NodePtr &cur) {
		if (levels[depth]) //if not first at this level
			levels[depth]->next = cur;
		else //if first at this level
			levels[depth - 1]->val = cur;
		levels[depth] = cur;
	};

	while (it != end) {
		if(depth<=0){
			std::cout << "ERROR: given string list is invalid (there are more ')' than '(' )\n" \
							"string value = [" << std::move(std::string(begin, end)) << "]";
			exit(EXIT_FAILURE);
		}
		switch (*it) {
		case '(':
			{
				if (depth + 1 == v_capacity) {
					v_capacity <<= 1;
					levels.resize(v_capacity, nullptr);
				}
				NodePtr cur = NewNode();
				connect(cur);
				depth++;
			}
			break;
		case ')':
			depth--;
			break;
		default:
			{
				NodePtr cur = NewNode();
				cur->val = *it;
				connect(cur);
			}
		} //switch
		it++;
	} //while
	if(depth){
		std::cout << "ERROR: given string list is invalid (there are more '(' than ')' )\n" \
						"string value = [" << std::move(std::string(begin, end)) << "]";
		exit(EXIT_FAILURE);
	}
}

void getRepr(std::string &dest, const NodePtr& list) {
	std::stringstream sstr;
	auto dfs = [&sstr](const NodePtr& list, auto && dfs) {
		if (!list){
			sstr <<')';
			return;
		}
		if (std::holds_alternative<NodePtr>(list->val)){
			sstr << '(';
			dfs(std::get<NodePtr>(list->val), dfs);
		}
		else
			sstr << std::get<char>(list->val);
		dfs(list->next, dfs);
	};
	dfs(list, dfs);
	dest = std::move(sstr.str());
	dest.pop_back();
}

void changeAllEntries(NodePtr &node, char a, const std::variant<char, NodePtr>& b){
	if (node) {
		if (std::holds_alternative<NodePtr>(node->val))
			changeAllEntries(std::get<NodePtr>(node->val), a, b);
		else if (std::get<char>(node->val) == a)
			if(std::holds_alternative<NodePtr>(b))
				node = std::get<NodePtr>(b);
			else
				node->val = std::get<char>(b);
		changeAllEntries(node->next, a, b);
	}
}

int main() {
	std::string input, res, b_str;
	char a;
	std::cin>>input>>a>>b_str;
	NodePtr list = NewNode();
	getList(list, input.begin(), input.end());
	if(b_str.size() == 1 && b_str[0] !='(')
		changeAllEntries(list, a, b_str[0]);
	else {
		NodePtr b_list = NewNode();
		getList(b_list, b_str.begin(), b_str.end());
		changeAllEntries(list, a, b_list);
	}
	getRepr(res, list);
	std::cout<<res;
	return 0;
}
