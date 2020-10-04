#include "Data.h"

Data::Data()
{
	ifstream input("./Tests/input.txt");
	
	if(input.is_open()) {
		while (getline(input, str)) {
			if(str != "\n"){
				strings.push_back(str);
			}
		}
	}
	else {
		cout << "Can't open input file" << '\n';
	}

	input.close();
}

void Data::StartDataProcessing()
{
	Recursion rec;
	Data data;

	ofstream output("./Tests/output.txt");

	if (output.is_open()) {
			while (data.strings.size() != 0) {
				std::size_t t = data.strings.front().find("Testing the");
				if(t == 0){
					output << '\n';
					output << data.strings.front() << "\n\n";
					data.strings.pop_front();
					continue;
				}
				else{
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
	}
	else {
		cout << "Can't open output file" << '\n';
	}

	output.close();


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
