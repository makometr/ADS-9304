#include <fstream>
#include <iostream>
#include <string>

#include "../lib/binary_tree.h"

void PrintTraverse(std::vector<std::variant<int, char, Operation>> vec) {
  for (const auto& it : vec) {
    if (std::holds_alternative<int>(it)) {
      std::cout << std::get<int>(it);
    } else if (std::holds_alternative<char>(it)) {
      std::cout << std::get<char>(it);
    } else {
      char c = ' ';
      Operation oper = std::get<Operation>(it);
      if (oper == Operation::kPlus) {
        c = '+';
      } else if (oper == Operation::kMinus) {
        c = '-';
      } else if (oper == Operation::kMultiply) {
        c = '*';
      } else {
        c = '?';
      }
      std::cout << c;
    }
    std::cout << ' ';
  }
  std::cout << '\n';
}

void PrintResult(BinaryTree& tree) {
  if (tree.IsCorrectBinaryTree()) {
    PrintTraverse(tree.PostfixTraverse());
    PrintTraverse(tree.PrefixTraverse());
    PrintTraverse(tree.InfixTraverse());
  } else {
    std::cout << "ERROR\n";
  }
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "Too small arguments.\n"
              << "А algebraic expression is expected after \"-s\" flag, "
              << "otherwise a file path is expected.\n\n"
              << "example: ./lab3 -s \"- * + a 2 c - 3 + e * f g \" Tests/test/test1.txt\n";
  } else {
    bool is_string = false;

    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];

      if (is_string) {
        is_string = false;
        BinaryTree expr(arg);
        expr.Simplify();
        PrintResult(expr);

      } else if (arg == "-s") {
        is_string = true;

      } else {
        std::ifstream file_in(arg);

        if (file_in.is_open()) {
          std::string str;
          std::getline(file_in, str);
          BinaryTree expr(str);
          expr.Simplify();
          PrintResult(expr);
          file_in.close();

        } else {
          std::cout << "Couldn't open the file.\n";
        } // else
      } // else
    } // for
  } // else
  return 0;
} // main