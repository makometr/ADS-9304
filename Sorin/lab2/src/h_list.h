#ifndef __H_LIST
#define __H_LIST

#include <iostream>
#include <variant>

template <typename base>
class VarNum {
public:
	bool IsVar = false;
	bool IsOp = false;
	char Var = 0;
	base Num;
};

template <typename base>
class h_list {
	using h_list_ptr = std::shared_ptr<h_list>;
public:
	h_list_ptr next{ nullptr };
	std::variant<h_list_ptr, VarNum<base>> value;
	void AddNext(void) {
		next = std::make_shared<h_list>();
	}
};

#endif // __H_LIST

