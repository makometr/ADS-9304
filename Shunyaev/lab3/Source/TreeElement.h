#pragma once
#include <variant>

template <typename T1>
class TreeElement
{
public:
	bool is_set = false;
	std::variant<T1, char> data_;

};

