#include <fstream>
#include <iostream>

#include "../lib/logical_expression.h"

void PrintAnalyzeResult(LogicalExpression& expr) {
  if (expr.Analyze()) {
    std::cout << "TRUE\n";
  } else {
    std::cout << "FALSE\n" << expr.GetError() << '\n';
  }
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "Too small arguments.\n"
              << "example: ./lab1 -s \"AND(A,B)\" Tests/test/test1.txt\n"
              << "А logical expression is expected after \"-s\" flag, "
              << "otherwise a file path is expected.\n";
  } else {
    bool is_string = false;

    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];

      if (is_string) {
        is_string = false;
        LogicalExpression expr = arg;
        PrintAnalyzeResult(expr);

      } else if (arg == "-s") {
        is_string = true;

      } else {
        std::ifstream file_in(arg);

        if (file_in.is_open()) {
          std::string str;
          std::getline(file_in, str);
          LogicalExpression expr = str;
          PrintAnalyzeResult(expr);
          file_in.close();

        } else {
          std::cout << "Couldn't open the file.\n";
        }
      }
    }
  }
  return 0;
}