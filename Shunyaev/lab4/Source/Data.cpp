#include "Data.h"

Data::Data()
{
	int digit;
	std::vector<int> temp;
	std::string str;

	std::getline(std::cin, str);
	std::istringstream iss(str);

	while (iss >> digit) {
		this->array_.push_back(digit);
		this->test_array.push_back(digit);
	}
}


Data::~Data()
{
	
}

void Data::PrintData(std::vector<int>& data)
{
	for (int i = 0; i < data.size(); i++) {
		std::cout << data[i] << ' ';
	}
}
