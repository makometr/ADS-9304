#pragma once

#include<iostream>
#include <fstream>
#include <string>
#include <list>
#include "Recursion.h"


using namespace std;

class Data
{
public:
	string str;
	string in;
	string out;
	list<string> strings;


	Data();
	static void StartDataProcessing();
	string SpaceErase(string str);

};

