#include "Test.h"


void Test::StartTests()
{

		int number = 1;
		Test test;

		test.InputTest();
		test.InputAnswer();
		while (test.tests.size() != 0) {
	
			if (test.tests.front() == test.answers.front()) {
				std::cout << "Program anwer: " << test.tests.front() << "\nTrue anwer:    " << test.answers.front()  <<"\nTest #" << number << " - True! \n\n";
			}
			else {
				std::cout << "Program anwer: " << test.tests.front() << "\nTrue anwer:    " << test.answers.front()  <<"\nTest #" << number << " - False! \n\n";
			}
			test.answers.pop_front();
			test.tests.pop_front();
			number++;
		}
		std::cout << std::endl;
	
}

void Test::InputTest()
{
	std::ifstream input1("./Tests/output.txt");

	if (input1.is_open()) { 
		while (getline(input1, this->str)) {
			std::size_t check = this->str.find("Testing the"); 
			
			if(check != 0 && this->str.length() != 0){
				this->tests.push_back(this->str);
			}
		}
	}
	else {
		std::cout << "Can't open test input-file" << '\n';
	}

	input1.close();
}

void Test::InputAnswer()
{
	std::ifstream input2("./Tests/true_output.txt");

	if (input2.is_open()) {
		while (getline(input2, this->str)) {
			std::size_t check = this->str.find("Testing the");  
			if(check != 0 && this->str.length() != 0){
				this->answers.push_back(this->str);
			}
		}
	}
	else {
		std::cout << "Can't open answer input-file" << '\n';
	}

	input2.close();
}
