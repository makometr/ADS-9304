
#include "hesh.h"

key_line::key_line() {

}
key_line::key_line(std::string NewName, std::string NewData) : Name(NewName), Data(NewData) {

}
key_line::key_line(std::string NewName, std::string NewData, int NewChain) : Name(NewName), Data(NewData), Chain(NewChain) {

}

hesh_table::hesh_table(unsigned int HTS, unsigned int KS) : HeshTableSize(HTS), KeySize(KS) {
	// выделение памяти для таблицы индексов
	std::unique_ptr<int[]> Fi(new int[HeshTableSize]);
	HeshTable = std::move(Fi);
	for (int i = 0; i < HeshTableSize; i++)
		HeshTable[i] = -1;
}
int hesh_table::AddToHeshTable(std::string NewName, std::string NewData) {
	int N = H(NewName);
	// число хеш-функции
	std::cout << "Hesh function number: " << N << '\n';
	if (HeshTable[N] == -1) {
		// если не было элементов с таким числом
		key_line KL(NewName, NewData);
		KeyTable.push_back(KL);
		HeshTable[N] = KeyTable.size() - 1;
		std::cout << "Index number " << N << ": " << -1 << "->" << HeshTable[N] << '\n';
		std::cout << "Added element number: " << HeshTable[N] << '\n';
		return 0;
	}
	else {
		int Count = 0;

		int SaveInd = HeshTable[N];
		std::cout << "Element number: " << SaveInd << '\n';
		std::cout << "Element chein: " << KeyTable[SaveInd].Chain << '\n';
		if (KeyTable[SaveInd].Name == NewName) {
			Count++;
			std::cout << "Element meeting: count = " << Count << '\n';
		}
		// переход дальше по цепочке
		while (KeyTable[SaveInd].Chain != -1) {
			SaveInd = KeyTable[SaveInd].Chain;
			std::cout << "Element number: " << SaveInd << '\n';
			std::cout << "Element chein: " << KeyTable[SaveInd].Chain << '\n';
			if (KeyTable[SaveInd].Name == NewName) {
				Count++;
				std::cout << "Element meeting: count = " << Count << '\n';
			}
		}
		// добавление элемента
		KeyTable[SaveInd].Chain = KeyTable.size();
		std::cout << "Chain element number " << SaveInd << ": " << -1 << "->" << KeyTable[SaveInd].Chain << '\n';
		std::cout << "Added element number: " << KeyTable[SaveInd].Chain << '\n';
		key_line KL(NewName, NewData);
		KeyTable.push_back(KL);
		return Count;
	}
}
int hesh_table::DelFromHeshTable(std::string DelName) {
	int N = H(DelName);
	// число хеш функции
	std::cout << "Hesh function number: " << N << '\n';
	if (HeshTable[N] == -1) {
		std::cout << "Element to be deleted is missing\n";
		return 0;
	}
	else {
		int SaveSaveInd = 0;

		int SaveInd = HeshTable[N];
		std::cout << "Element number: " << SaveInd << '\n';
		std::cout << "Element chein: " << KeyTable[SaveInd].Chain << '\n';
		// если удаляется первый элемент цепочки
		if (KeyTable[SaveInd].Name == DelName) {
			HeshTable[N] = KeyTable[SaveInd].Chain;
			KeyTable.erase(KeyTable.begin() + SaveInd);
			for (int i = 0; i < HeshTableSize; i++)
				if (HeshTable[i] >= SaveInd)
					HeshTable[i]--;
			for (int i = 0; i < KeyTable.size(); i++)
				if (KeyTable[i].Chain >= SaveInd)
					KeyTable[i].Chain--;
			std::cout << "Element |" << DelName << "| has been deleted" << '\n';
			return 1;
		}
		while (KeyTable[SaveInd].Chain != -1) {
			SaveSaveInd = SaveInd;
			SaveInd = KeyTable[SaveInd].Chain;
			std::cout << "Element number: " << SaveInd << '\n';
			std::cout << "Element chein: " << KeyTable[SaveInd].Chain << '\n';
			// если удаляется не первый элемент цепочки
			if (KeyTable[SaveInd].Name == DelName) {
				KeyTable[SaveSaveInd].Chain = KeyTable[SaveInd].Chain;
				KeyTable.erase(KeyTable.begin() + SaveInd);
				for (int i = 0; i < HeshTableSize; i++)
					if (HeshTable[i] >= SaveInd)
						HeshTable[i]--;
				for (int i = 0; i < KeyTable.size(); i++)
					if (KeyTable[i].Chain >= SaveInd)
						KeyTable[i].Chain--;
				std::cout << "Element |" << DelName << "| has been deleted" << '\n';
				return 1;
			}
		}
		std::cout << "Element to be deleted is missing\n";
		return 0;
	}
}
int hesh_table::Ord(char C) {
	if (std::isdigit(C))
		return C - '0';
	else if (C >= 'a' && C <= 'z') {
		return C - 'a' + 10; // 'a'...'z' стоят после цифр
	}
	else if (C >= 'A' && C <= 'Z') {
		return C - 'A' + 10 + 'z' - 'a' + 1;// // 'A'...'Z' стоят после 'a'...'z'
	}
	else
		throw std::invalid_argument("Error while entering expression");
}
int hesh_table::H(std::string Name) {
	int Sum = 0;
	// подсчет числа для ключа
	for (int i = 0; i < Name.size(); i++)
		Sum += Ord(Name[i]);
	int Mod = HeshTableSize;
	// получение числа хеш-функции для ключа
	Sum %= Mod;
	return Sum;
}
void hesh_table::ReadKey(std::string& Key, std::stringstream& Stream) {
	char C = 0;
	if (!Stream.get(C))
		throw std::invalid_argument("Error while entering expression");
	for (int i = 0; (std::isdigit(C) || (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z')) && (i < KeySize); i++) {
		Key += C;
		// выход если ключ закончился
		if (Stream.get(C).eof())
			return;
		if (Stream.fail())
			throw std::invalid_argument("Error while entering expression");
	}
	throw std::invalid_argument("Error while entering expression");
}

