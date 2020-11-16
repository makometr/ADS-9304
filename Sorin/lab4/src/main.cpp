#include <string>
#include "sort.h"

int main() {
	try
	{
		sort_list<double> SL;

		bool Res = 0;
		std::string Str;
		if (!std::getline(std::cin, Str))
			throw std::runtime_error("Error while reading from stream");
		std::stringstream Stream(Str);
		SL.ReadList(Stream);
		SL.StrandSort();

	}
	catch (const std::exception& Error)
	{
		std::cout << Error.what();
	}
	return 0;
}