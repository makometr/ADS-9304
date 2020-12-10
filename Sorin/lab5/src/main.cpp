#include <string>
#include "hesh.h"

std::stringstream GetLine(void) {
	std::string Str;
	if (!std::getline(std::cin, Str))
		throw std::runtime_error("Error while reading from stream");
	std::stringstream Stream(Str);
	return Stream;
}

std::ostream& operator<<(std::ostream& os, hesh_table& HT) {
	os << '|';
	for (int it = 0; it < HT.HeshTableSize; it++) {
		os.width(2);
		os << HT.HeshTable[it] << '|';
	}
	os << "\n\n";
	for (int it = 0; it < HT.KeyTable.size(); it++) {
		os << '|';
		os.width(2);
		os << HT.KeyTable[it].Chain;
		os << '|';
		std::string s = HT.KeyTable[it].Name;
		os.width(HT.KeySize);
		os << s;
		os << '|';
		os << HT.KeyTable[it].Data;
		os << '|';
		os << '\n';
	}
	return os << '\n';
}

int main() {
	try
	{
		unsigned int HTS = 5, MKS = 10;
		/*std::cout << "Enter hesh table size: ";
		std::cin >> HTS;
		std::cout << "\n";
		std::cout << "Enter max key size: ";
		std::cin >> MKS;
		std::cout << "\n";*/

		hesh_table HT(HTS, MKS);
		int Res = 0;
		std::string Key;
		while (1) {
			Key = "";
			std::stringstream Stream = GetLine();
			char C = 0;
			if (Stream.get(C).eof())
				break;
			if (C != '1')
				throw std::invalid_argument("Error while entering expression");
			if ((C = Stream.get()) != ')')
				throw std::invalid_argument("Error while entering expression");
			HT.ReadKey(Key, Stream);
			std::stringstream Stream2 = GetLine();
			std::string Data;
			if ((C = Stream2.get()) != '2')
				throw std::invalid_argument("Error while entering expression");
			if ((C = Stream2.get()) != ')')
				throw std::invalid_argument("Error while entering expression");
			Data = Stream2.str().erase(0, 2);
			Res = HT.AddToHeshTable(Key, Data);
			std::cout << "\x1B[2J\x1B[H";
			std::cout << "Number of element meetings: " << Res;
			std::cout << "\nElement added\n\n";
			std::cout << HT;
		}

	}
	catch (const std::exception& Error)
	{
		std::cout << Error.what();
	}
	return 0;
}
