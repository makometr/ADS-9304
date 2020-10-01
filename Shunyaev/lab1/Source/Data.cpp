#include "Data.h"
#define IN1  "./Tests/input1.txt"
#define OUT1 "./Tests/output1.txt"
#define IN2	 "./Tests/input2.txt"
#define OUT2 "./Tests/output2.txt"
#define IN3  "./Tests/input3.txt"
#define OUT3 "./Tests/output3.txt"

Data::Data(int i)
{
	switch (i)
	{
	case 1:
		in = IN1;
		out = OUT1;
		break;

	case 2:
		in = IN2;
		out = OUT2;
		break;

	case 3:
		in = IN3;
		out = OUT3;
		break;

	default:
		break;
	}

	ifstream input(in);
	
	if (input.is_open()) {
		while (getline(input, str)) {
			strings.push_back(str);
		}
	}
	else {
		cout << "Can't open input file" << '\n';
	}

	input.close();
}

void Data::start()
{
	Recursion rec;

	for (int i = 1; i < 4; i++) {
		
		Data data(i);
		ofstream output(data.out);

		if (output.is_open()) {
				while (data.strings.size() != 0) {

					string temp = data.SpaceErase(data.strings.front());

					if (rec.IsBrackets(temp, 0, 0)) {
						output << data.strings.front() << " - THIS IS A BRACKETS" << '\n';
						data.strings.pop_front();

					}
					else {
						output << data.strings.front() << " - THIS IS NOT A BRACKETS" << '\n';
						data.strings.pop_front();
					}
				}	
		}
		else {
			cout << "Can't open output file" << '\n';
		}

		output.close();
	}

}

string Data::SpaceErase(string str)
{
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			str.erase(i, 1);
			--i;
		}
	}
	return str;
}
