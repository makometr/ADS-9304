#include <fstream>
#include <iostream>

#include "../lib/logical_expression.h"

int main(int argc, char** argv) {
  std::ifstream file_in(argv[1]);

  if (file_in.is_open()) {
    std::string str;
    std::getline(file_in, str);

    LogicalExpression expr = str;

    if (expr.Analyze()) {
      std::cout << "TRUE";
    } else {
      std::cout << "FALSE\n" << expr.GetError();
    }
    
    file_in.close();
  } else {
    std::cout << "Couldn't open the file.\nusage: ./lab1 filename\n";
  }

  return 0;
}