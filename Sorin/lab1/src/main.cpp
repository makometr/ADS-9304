
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

bool IsBrackets(std::stringstream& Stream) {
	char c = 0;

	if (!Stream.get(c))
		throw std::invalid_argument("Error while entering expression\n");
	if (c == 'A') {
		return true;
	}
	else if (c == 'B') {
		return true;
	}
	else if (c == '(') {
		bool Res1, Res2;
		Res1 = IsBrackets(Stream);
		if (!Stream.get(c))
			throw std::invalid_argument("Error while entering expression\n");
		if (c != ' ')
			throw std::invalid_argument("Missed space\n");
		Res2 = IsBrackets(Stream);
		if (!Stream.get(c))
			throw std::invalid_argument("Error while entering expression\n");
		if (c != ')')
			throw std::invalid_argument("Missed \')\'\n");
		return Res1 && Res2;
	}
	else
		throw std::invalid_argument("Missed \'A\', \'B\' or \'(\'\n");
}

int main() {
	try
	{
		bool Res = 0;
		std::string Str;
		if (!std::getline(std::cin, Str))
			throw std::runtime_error("Error while reading from stream\n");
		std::stringstream Stream(Str);
		Res = IsBrackets(Stream);
		if (Res == true)
			std::cout << "These are brackets" << std::endl;
		else
			std::cout << "These are not brackets" << std::endl;
	}
	catch (const std::exception& Error)
	{
		std::cout << Error.what();
	}
	return 0;
}
