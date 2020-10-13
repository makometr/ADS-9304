#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stack>
#include <variant>

#include "H_List.h"

bool isCorrect(const std::string& list);

int main(int argc, char** argv){
    if (argc < 3){
        std::cout << "Команда для запуска программы: ./lab2 /path/to/input /path/to/output" << std::endl;
        return 1;
    }
    else{
        std::ifstream in(argv[1]);
        if (!in.is_open()){
            std::cout << argv[1] << ": No such file or directory" << std::endl;
            return 1; 
        }
        std::ofstream out(argv[2]);
        if (!out.is_open()){
            std::cout << argv[2] << ": No such file or directory" << std::endl;
            return 1;
        }
        std::string list;
        H_List h_list;
        char elem;
        while(getline(in, list)){
            if (list.find('(') != std::string::npos){
                if (!isCorrect(list)){
                    out << "The list isn't correct." << std::endl;
                    in.close();
                    out.close();
                    return 1;
                }
                int i = 0;
                h_list.read_h_list(list,i);
            }
            else{
                elem = list[list.length()-1];
                h_list.set_element(elem);
            }
        }
        in.close();

        h_list.browse(h_list.head);
        if (h_list.get_is_elem()){
            out << elem << " is found\n";
        }
        else{
            out << elem << " isn't found\n";
        }

        h_list.free_list(h_list.head);
        out.close();
    }
    return 0;
}

bool isCorrect(const std::string& list){
    std::stack<char> Stack;
    if (list[0] != '('){
        return false;
    }
    for (char i : list){
        if (i == '('){
            Stack.push(i);
        }
        if (i == ')'){
            if (Stack.empty()){
                return false;
            }
            Stack.pop();
        }
    }
    return Stack.empty();
}