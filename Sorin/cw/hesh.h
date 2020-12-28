#ifndef __HESH_H
#define __HESH_H

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

// класс - одна строчка из таблицы с данными
class key_line {
public:
	// конструкторы
	key_line();
	key_line(std::string NewName, std::string NewData);
	key_line(std::string NewName, std::string NewData, int NewChain);
	// ключ
	std::string Name;
	// данные
	std::string Data;
	// чепочка
	int Chain = -1;
};

// класс - хеш-таблица
class hesh_table {
public:
	// размер таблицы индексов
	unsigned int HeshTableSize = 11;
	// максимальный размер ключа
	unsigned int KeySize = 8;
	// таблица с данными
	std::vector<key_line> KeyTable;
	// таблица индексов
	std::unique_ptr<int[]> HeshTable;
	// конструктор
	hesh_table(unsigned int HTS, unsigned int KS);
	// добавление элемента в хеш-таблицу
	int AddToHeshTable(std::string NewName, std::string NewData);
	// удаление элемента из хеш-таблицы
	int DelFromHeshTable(std::string DelName);
	// возвращает номер символа
	int Ord(char C);
	// хеш-функция
	int H(std::string Name);
	// считывание ключа
	void ReadKey(std::string& Key, std::stringstream& Stream);
};

#endif // __HESH_H
