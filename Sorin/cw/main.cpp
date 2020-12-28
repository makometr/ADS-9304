#include <string>
#include "hesh.h"

// считывание линии из потока 
std::stringstream GetLine(void) {
	std::string Str;
	if (!std::getline(std::cin, Str))
		throw std::runtime_error("Error while reading from stream");
	std::stringstream Stream(Str);
	return Stream;
}

// перегрузка оператора вывода для вывода хеш-таблицы
std::ostream& operator<<(std::ostream& os, hesh_table& HT) {
	// вывод таблицы индексов
	os << "Index table:\n\n";
	os << '|';
	for (int it = 0; it < HT.HeshTableSize; it++) {
		os.width(2);
		os << HT.HeshTable[it] << '|';
	}
	os << "\n\n";
	// вывод таблицы с данными и цепочками
	os << "Data table:\n|chain|key|Data|\n\n";
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
		// размер таблицы индексов и максимальный размер ключа
		unsigned int HTS = 5, MKS = 10;
		
		// создание пустой таблицы
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
			// считывание ключа
			HT.ReadKey(Key, Stream);
			// считывание данных
			std::stringstream Stream2 = GetLine();
			if (Stream2.get(C).eof()) {
				// чистка экрана
				std::cout << "\x1B[2J\x1B[H";
				// вывод самой таблицы
				std::cout << HT;
				// удаление элемента из таблицы
				Res = HT.DelFromHeshTable(Key);
			}
			else {
				std::string Data;
				if ((C) != '2')
					throw std::invalid_argument("Error while entering expression");
				if ((C = Stream2.get()) != ')')
					throw std::invalid_argument("Error while entering expression");
				Data = Stream2.str().erase(0, 2);
				// чистка экрана
				std::cout << "\x1B[2J\x1B[H";
				// вывод самой таблицы
				std::cout << HT;
				// добавление элемента в таблицу
				Res = HT.AddToHeshTable(Key, Data);
			}
			// информация о колличестве встреченных элементов
			std::cout << "Number of element meetings: " << Res << "\n\n";
			// вывод самой таблицы
			std::cout << HT;
		}

	}
	catch (const std::exception& Error) // отлавливание ошибок
	{
		// вывод информации об ошибке
		std::cout << Error.what();
	}
	return 0;
}
