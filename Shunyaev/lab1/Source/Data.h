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


	Data(int i);
	static void start();
	string SpaceErase(string str);

};

