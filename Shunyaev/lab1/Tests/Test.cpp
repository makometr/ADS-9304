#include "Test.h"


void Test::StartTests()
{

		int number = 1;
		Test test;

		test.InputTest();
		test.InputAnswer();
		while (test.tests.size() != 0) {
	
			if (test.tests.front() == test.answers.front()) {
				cout << "\tTest #" << number << " - True! \n";
			}
			else {
				cout << "\tTest #" << number << " - False! \n";
			}
			test.answers.pop_front();
			test.tests.pop_front();
			number++;
		}
		cout << endl;
	
}

void Test::InputTest()
{
	ifstream input1("./Tests/output.txt");

	if (input1.is_open()) { 
		while (getline(input1, this->str)) {
			std::size_t check = this->str.find("Testing the"); 
			
			if(check != 0 && this->str.length() != 0){
				this->tests.push_back(this->str);
			}
		}
	}
	else {
		cout << "Can't open test input-file" << '\n';
	}

	input1.close();
}

void Test::InputAnswer()
{
	ifstream input2("./Tests/true_output.txt");

	if (input2.is_open()) {
		while (getline(input2, this->str)) {
			std::size_t check = this->str.find("Testing the");  
			if(check != 0 && this->str.length() != 0){
				this->answers.push_back(this->str);
			}
		}
	}
	else {
		cout << "Can't open answer input-file" << '\n';
	}

	input2.close();
}
