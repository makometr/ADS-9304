#include "Test.h"
#define IN1  "./Tests/output1.txt"
#define ANS1 "./Tests/true_output1.txt"
#define IN2	 "./Tests/output2.txt"
#define ANS2 "./Tests/true_output2.txt"
#define IN3  "./Tests/output3.txt"
#define ANS3 "./Tests/output3.txt"

Test::Test(int i) {
	switch (i)
	{
	case 1:
		in_test = IN1;
		in_answer = ANS1;
		break;

	case 2:
		in_test = IN2;
		in_answer = ANS2;
		break;

	case 3:
		in_test = IN3;
		in_answer = ANS3;
		break;

	default:
		break;
	}
	
}

void Test::start()
{
	for (int i = 1; i < 4; i++) {
		int number = 1;
		Test test(i);

		Test::InputTest(&test);
		Test::InputAnswer(&test);
		cout << "Testing #" << i << " output-file! \n\n";
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
}

void Test::InputTest(Test* test)
{
	ifstream input1(test->in_test);

	if (input1.is_open()) {
		while (getline(input1, test->str)) {
			test->tests.push_back(test->str);
		}
	}
	else {
		cout << "Can't open test input-file" << '\n';
	}

	input1.close();
}

void Test::InputAnswer(Test* test)
{
	ifstream input2(test->in_answer);

	if (input2.is_open()) {
		while (getline(input2, test->str)) {
			test->answers.push_back(test->str);
		}
	}
	else {
		cout << "Can't open answer input-file" << '\n';
	}

	input2.close();
}
