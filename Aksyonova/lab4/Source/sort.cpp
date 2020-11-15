#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
 
std::ostream& operator << (std::ostream& out, const std::vector<int>& vec) {
	out << '[';
	for (int i = 0; i < vec.size(); i++) {
		if (i == vec.size() - 1) {
			out << vec[i];
			break;
		}
		out << vec[i] << ", ";
	}
	out << ']';
	return out;
}
 
void sortc(std::vector<int>& vec){
	int size = vec.size();
	int count = 0;
	int step = size;
	while (step > 1) {
		count += 1;
		std::cout << "This is " << count << " iteration of sorting" << '\n';
		step = std::max(1, step/= 1.247f);
		for (int i = 0; i + step < size;++i) {
			if (vec[i]  > vec[i + step] ) {
				std::cout << "We will change this elements: " << vec[i] << "(" << i << ")" << " and " << vec[i + step] << "(" << i + step << ")" << '\n';
				std::swap(vec[i], vec[i + step]);
			}
		}
 
		std::cout << vec << '\n';
	}
 
}
 
void checkStr(std::string& str) {
	for (int i = 0; i < str.size(); i++) {
		if (!isdigit(str[i])&&str[i]!=' ') {
			str.erase(i, 1);
			i -= 1;
		}
	}
}
int main(int argc, char** argv) {
	std::string str1;
	std::vector<int> vec;
	std::vector<int> vecToCheck;
	int value;
 
	if (argc < 2)
		std::getline(std::cin, str1);
	else
		str1 = argv[1];
 
	checkStr(str1);
	std::stringstream ss(str1);
	while (ss >> value) {
		vec.push_back(value);
 
		if (ss.peek() == ' ') {
			ss.ignore();
		}
	}
	vecToCheck = vec;
	sortc(vec);
	std::cout << "This is sorted array" << '\n';
	std::cout << vec;
	std::cout << '\n';
	std::sort(vecToCheck.begin(), vecToCheck.end());
	if (vec == vecToCheck) {
		std::cout << "They are identical" << std::endl;
	}
	else {
		std::cout << "Incorrect!" << std::endl;
	}
	return 0;
}
