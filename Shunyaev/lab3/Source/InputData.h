#pragma once
#include <string>
#include <list>
#include <fstream>
#include <iostream>

class InputData
{
public:
	std::list<std::string> list;
	std::ifstream file_;

	InputData();
};

