
#include <string>
#include "BinTree.h"

int main() {
	try
	{
		bin_tree<char> BT;

		bool Res = 0;
		std::string Str;
		if (!std::getline(std::cin, Str))
			throw std::runtime_error("Error while reading from stream");
		std::stringstream Stream(Str);
		BT.ReadBT(Stream);
		Res = BT.IsIdenticalNodes();
		if (Res == true)
			std::cout << "There are identical nodes" << std::endl;
		else
			std::cout << "All nodes are different" << std::endl;
		system("pause");
	}
	catch (const std::exception& Error)
	{
		std::cout << Error.what();
	}
	return 0;
}