#include <fstream>
#include <iostream>
#include <string>

#include "../lib/algebraic_expression.h"
#include "../lib/my_exception.h"

void PrintAnalyzeResult(bool is_correct_expr, const MyException& err) {
  if (is_correct_expr) {
    std::cout << "TRUE\n";
  } else {
    std::cout << "FALSE\n" << err << '\n';
  }
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "Too small arguments.\n"
              << "А algebraic expression is expected after \"-s\" flag, "
              << "otherwise a file path is expected.\n\n"
              << "example: ./lab2 -s \"+ 0 (* 1 2)\" Tests/test/test1.txt\n";
  } else {
    bool is_string = false;

    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];

      if (is_string) {
        is_string = false;
        AlgebraicExpression expr(arg);
        bool is_correct_expr = expr.Analyze();
        PrintAnalyzeResult(is_correct_expr, expr.GetError());

      } else if (arg == "-s") {
        is_string = true;

      } else {
        std::ifstream file_in(arg);

        if (file_in.is_open()) {
          std::string str;
          std::getline(file_in, str);
          AlgebraicExpression expr(str);
          bool is_correct_expr = expr.Analyze();
          PrintAnalyzeResult(is_correct_expr, expr.GetError());
          file_in.close();

        } else {
          std::cout << "Couldn't open the file.\n";
        }
      }
    }
  }
}