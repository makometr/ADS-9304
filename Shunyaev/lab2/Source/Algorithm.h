#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include "HierarchicalList.h"

class Algorithm
{
	
public:
	static void StartDataProcessing();

	bool IsCorrect(std::shared_ptr<HierarchicalList> h_list);
	std::list<std::string> InputData();
	
};

