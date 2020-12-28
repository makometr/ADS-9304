#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../lib/treap.h"

enum class Operation {
  kInsert = 0,
  kRemove,
  kCountAndThenInsert,
  kCount,
  kPrint,
  kExit
};

template <typename T>
void Analyze(const std::string& str, Treap<T> treap) {
  Operation current_operation = Operation::kInsert;
  std::stringstream ss;
  std::string in;
  ss << str;
  bool is_end = false;
  bool is_check_str = true;

  while (!is_end) {
    if (is_check_str && !(ss >> in)) {
      is_check_str = false;
    }
    if (!is_check_str) {
      std::cout << "Ввод: ";
      std::cin >> in;
      std::cout << '\n';
    }

    if (in == "#Insert") {
      current_operation = Operation::kInsert;
    } else if (in == "#Remove") {
      current_operation = Operation::kRemove;
    } else if (in == "#Task") {
      current_operation = Operation::kCountAndThenInsert;
    } else if (in == "#Count") {
      current_operation = Operation::kCount;
    } else if (in == "#Print") {
      current_operation = Operation::kPrint;
      std::cout << '\n' << treap << "\n\n";
    } else if (in == "#Exit") {
      current_operation = Operation::kExit;
      is_end = true;
    } else {
      if (current_operation == Operation::kInsert) {
        treap.Insert(in);
      } else if (current_operation == Operation::kRemove) {
        treap.Remove(in);
      } else if (current_operation == Operation::kCount) {
        std::cout << "Count = " << treap.Count(in) << " (для элемента \"" << in
                  << "\")" << '\n';
      } else if (current_operation == Operation::kCountAndThenInsert) {
        size_t len = treap.CountAndThenInsert(in);
        std::cout << "Count = " << len << " (для элемента \"" << in << "\")"
                  << '\n';
      } else if (current_operation == Operation::kPrint) {
        std::cout << '\n' << treap << "\n\n";
      }
    }
  }
  std::cout << '\n';
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "Слишком мало аргументов.\n"
              << "Выражение ожидается после флага \"-s\", "
              << "иначе ожидается путь к файлу.\n\n"
              << "например: ./cw -s \"2 3 1 2 3 5 6 #Remove 3 5 6 #Task 2\" "
                 "Tests/test/test1.txt\n";
  } else {
    bool is_string = false;

    for (int i = 1; i < argc; ++i) {
      bool is_open = false;
      std::string arg = argv[i];
      Treap<std::string> treap;

      if (arg == "-s" && !is_string) {
        is_string = true;
      } else {
        std::string str = arg;
        if (!is_string) {
          std::ifstream file_in(arg);
          if (file_in.is_open()) {
            is_open = true;
            std::getline(file_in, str);
            file_in.close();
          } else {
            std::cout << "Не удалось открыть файл.\n";
          }
        }
        if (!(!is_string && !is_open)) {
          Analyze<std::string>(str, treap);
        }
      }
    }  // for
  }    // else
  return 0;
}  // main