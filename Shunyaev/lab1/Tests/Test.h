#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include "string"

using namespace std;

class Test
{
public:
	string str;
	string in_test;
	string in_answer;
	list<string> tests;
	list<string> answers;

	static void StartTests();
	void InputTest();
	void InputAnswer();
};

