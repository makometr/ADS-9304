#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include "string"



class Test
{
public:
	std::string str;
	std::string in_test;
	std::string in_answer;
	std::list<std::string> tests;
	std::list<std::string> answers;

	static void StartTests();
	void InputTest();
	void InputAnswer();
};

