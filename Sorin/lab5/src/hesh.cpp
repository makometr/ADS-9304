
#include "hesh.h"

key_line::key_line() {

}
key_line::key_line(std::string NewName, std::string NewData) : Name(NewName), Data(NewData) {

}
key_line::key_line(std::string NewName, std::string NewData, int NewChain) : Name(NewName), Data(NewData), Chain(NewChain) {

}

hesh_table::hesh_table(unsigned int HTS, unsigned int KS) : HeshTableSize(HTS), KeySize(KS) {
	std::unique_ptr<int[]> Fi(new int[HeshTableSize]);
	HeshTable = std::move(Fi);
	for (int i = 0; i < HeshTableSize; i++)
		HeshTable[i] = -1;
}
int hesh_table::AddToHeshTable(std::string NewName, std::string NewData) {
	int N = H(NewName);
	if (HeshTable[N] == -1) {
		key_line KL(NewName, NewData);
		KeyTable.push_back(KL);
		HeshTable[N] = KeyTable.size() - 1;
		return 0;
	}
	else {
		int Count = 0;
		int SaveInd = HeshTable[N];
		if (KeyTable[SaveInd].Name == NewName)
			Count++;
		while (KeyTable[SaveInd].Chain != -1) {
			SaveInd = KeyTable[SaveInd].Chain;
			if (KeyTable[SaveInd].Name == NewName)
				Count++;
		}
		KeyTable[SaveInd].Chain = KeyTable.size();
		key_line KL(NewName, NewData);
		KeyTable.push_back(KL);
		return Count;
	}
}
int hesh_table::Ord(char C) {
	if (std::isdigit(C))
		return C - '0';
	else if (C >= 'a' && C <= 'z') {
		return C - 'a' + 10;
	}
	else if (C >= 'A' && C <= 'Z') {
		return C - 'A' + 10 + 'z' - 'a' + 1;
	}
	else
		throw std::invalid_argument("Error while entering expression");
}
int hesh_table::H(std::string Name) {
	int Sum = 0;
	for (int i = 0; i < Name.size(); i++)
		Sum += Ord(Name[i]);
	int Mod = HeshTableSize;
	Sum %= Mod;
	return Sum;
}
void hesh_table::ReadKey(std::string& Key, std::stringstream& Stream) {
	char C = 0;
	if (!Stream.get(C))
		throw std::invalid_argument("Error while entering expression");
	for (int i = 0; (std::isdigit(C) || (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z')) && (i < KeySize); i++) {
		Key += C;
		if (Stream.get(C).eof())
			return;
		if (Stream.fail())
			throw std::invalid_argument("Error while entering expression");
	}
	throw std::invalid_argument("Error while entering expression");
}

