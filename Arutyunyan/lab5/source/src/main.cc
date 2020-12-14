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
};

template <typename T>
void Analyze(const std::string& str, Treap<T> treap) {
  Operation current_operation = Operation::kInsert;
  std::stringstream ss;
  std::string in;
  ss << str;

  while (ss >> in) {
    if (in == "#Insert") {
      current_operation = Operation::kInsert;
    } else if (in == "#Remove") {
      current_operation = Operation::kRemove;
    } else if (in == "#Task") {
      current_operation = Operation::kCountAndThenInsert;
    } else if (in == "#Count") {
      current_operation = Operation::kCount;
    } else {
      if (current_operation == Operation::kInsert) {
        treap.Insert(in);
      } else if (current_operation == Operation::kRemove) {
        treap.Remove(in);
      } else if (current_operation == Operation::kCount) {
        std::cout << "Count = " << treap.Count(in) << " (for the \"" << in
                  << "\" element)" << '\n';
      } else if (current_operation == Operation::kCountAndThenInsert) {
        std::cout << "Count = " << treap.CountAndThenInsert(in)
                  << " (for the \"" << in << "\" element)" << '\n';
      }
    }
  }
  std::cout << treap << '\n';
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "Too small arguments.\n"
              << "А expression is expected after \"-s\" flag, "
              << "otherwise a file path is expected.\n\n"
              << "example: ./lab5 -s \"2 3 1 2 3 5 6 Remove 3 5 6 Task 2\" "
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
            std::cout << "Couldn't open the file.\n";
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