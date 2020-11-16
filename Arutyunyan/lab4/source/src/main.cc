#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../lib/merge_sort.h"

void FillVector(std::vector<std::string>& vec, std::stringstream& sstr) {
  std::string str;
  while (sstr >> str) {
    vec.push_back(str);
  }
}

void print(std::vector<std::string> vec) {
  for (auto it : vec) {
    std::cout << it << ' ';
  }
  std::cout << '\n';
}

void Sort(std::vector<std::string>& vec) {
  std::cout << "In:\n    ";
  print(vec);
  MergeSort<std::vector<std::string>::iterator, std::string>(vec.begin(),
                                                             vec.end());
  std::cout << "Out:\n    ";
  print(vec);
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout
        << "Too small arguments.\n"
        << "А expression is expected after \"-s\" flag, "
        << "otherwise a file path is expected.\n\n"
        << "example: ./lab4 -s \"2 3 0 18 3 299 11 94\" Tests/test/test1.txt\n";
  } else {
    bool is_string = false;

    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];
      std::stringstream sstr;
      std::vector<std::string> vec;
      std::vector<std::string> vec_copy;
      if (is_string) {
        is_string = false;
        sstr << arg;
        FillVector(vec, sstr);
        vec_copy.resize(vec.size());
        std::copy(vec.begin(), vec.end(), vec_copy.begin());
        std::sort(vec_copy.begin(), vec_copy.end());
        Sort(vec);
        std::cout << "std::sort:\n    ";
        print(vec_copy);

      } else if (arg == "-s") {
        is_string = true;

      } else {
        std::ifstream file_in(arg);

        if (file_in.is_open()) {
          std::string str;
          std::getline(file_in, str);
          sstr << str;
          FillVector(vec, sstr);
          vec_copy.resize(vec.size());
          std::copy(vec.begin(), vec.end(), vec_copy.begin());
          std::sort(vec_copy.begin(), vec_copy.end());
          Sort(vec);
          std::cout << "std::sort:\n    ";
          print(vec_copy);

          file_in.close();

        } else {
          std::cout << "Couldn't open the file.\n";
        }  // else
      }    // else
    }      // for
  }        // else
  return 0;
}  // main
