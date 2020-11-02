#include "HierarchicalList.h"

HierarchicalList::~HierarchicalList()
{
}

void HierarchicalList::PushBack(std::shared_ptr<Node> element)
{
	if (this->head_ == nullptr) {
		this->head_ = element;
		this->end_ = this->head_;
	}
	else {
		this->end_->next = element;
		this->end_ = element;
	}

	this->length_++;
}

bool HierarchicalList::IsAtom(std::shared_ptr<Node> element)
{
	if (std::holds_alternative<std::shared_ptr<HierarchicalList>>(element->value)) {
		return false;
	}
	else {
		return true;
	}
}

std::shared_ptr<Node> HierarchicalList::Front()
{
	return this->head_;
}

std::shared_ptr<Node> HierarchicalList::Back()
{
	return this->end_;
}

int HierarchicalList::Length()
{
	return this->length_;
}

std::shared_ptr<HierarchicalList> HierarchicalList::CreateHList(std::string& str, int& position)
{
	std::shared_ptr<HierarchicalList> h_list = std::make_shared<HierarchicalList>();
	for (position; position < str.length(); position++) {
		if (str[position] == '(') {
			if(str[position+1] == ')'){
				std::shared_ptr<Node> node = std::make_shared<Node>();
				std::shared_ptr<HierarchicalList> temp = std::make_shared<HierarchicalList>();
				temp->head_ = nullptr;
				temp->end_ = nullptr;
				node->value = temp;
				h_list->PushBack(node); 
			}
			else{
				std::shared_ptr<Node> node = std::make_shared<Node>();
				std::shared_ptr<HierarchicalList> temp = HierarchicalList::CreateHList(str, ++position);
				node->value = temp;
				h_list->PushBack(node);
			}
			std::shared_ptr<Node> node = std::make_shared<Node>();
			std::shared_ptr<HierarchicalList> temp = HierarchicalList::CreateHList(str, ++position);
			node->value = temp;
			h_list->PushBack(node);
		}
		else if (str[position] == ')') {
			break;
		}
		else {
			std::shared_ptr<Node> atom = std::make_shared<Node>();
			atom->value = str[position];
			h_list->PushBack(atom);
		}
	}
	return h_list;
}


