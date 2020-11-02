#pragma once
#include <variant>
#include <string>
#include <memory>

class HierarchicalList;

struct Node
{
	std::shared_ptr<Node> next = nullptr;
	std::variant<std::shared_ptr<HierarchicalList>, char> value;
};

class HierarchicalList
{
public:

	~HierarchicalList();

	void PushBack(std::shared_ptr<Node>);
	bool IsAtom(std::shared_ptr<Node>);
	

	static std::shared_ptr<HierarchicalList> CreateHList(std::string& str, int& position);

	std::shared_ptr<Node> Front();
	std::shared_ptr<Node> Back();
	int Length();

private:
	int length_ = 0;
	std::shared_ptr<Node> head_ = nullptr;
	std::shared_ptr<Node> end_ = nullptr;
};

