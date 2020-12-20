#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


class Data
{
public:
	std::vector<int> array_;
	std::vector<int> test_array;

	Data();
	~Data();

	void PrintData(std::vector<int>& data);
};

