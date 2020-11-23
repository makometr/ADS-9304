#include "InputData.h"

InputData::InputData()
{
	file_.open("./Tests/input.txt");
	std::string str;

	if (file_.is_open()) {
		while (std::getline(file_, str)) {
			std::cout << str << '\n';
			this->list.push_back(str);
		}
	}
	else {
		std::cout << "Can't open input file!" << std::endl;
	}

	file_.close();
}
