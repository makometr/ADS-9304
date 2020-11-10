#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stack>
#include <variant>

#include "H_List.h"

bool isCorrect(const std::string& list);

int main(int argc, char** argv){
    std::string list;
    H_List h_list;
    char elem;
    if (argc < 3){
        std::cout << "list = ";
        getline(std::cin, list);
        std::cout << "Element to search for: ";
        std::cin >> elem;
        if (!isCorrect(list)){
            std::cout << "The list isn't correct." << std::endl;
            return 1;
        }
        int i = 0;
        h_list.read_h_list(list,i);
        h_list.set_element(elem);

        h_list.browse(h_list.head);
        if (h_list.get_is_elem()){
            std::cout << elem << " is found (" << h_list.get_number_elem() << " times)" << std::endl;
        }
        else{
            std::cout << elem << " isn't found" << std::endl;
        }

        h_list.free_list(h_list.head);
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
        std::string string;
        while(getline(in, string)){
            if (string.find('(') != std::string::npos){
                list = string;
            }
            else{
                if (string.length() > 24){
                    std::cout << "More than 1 search item entered." << std::endl;
                    in.close();
                    out.close();
                    return 1;
                }
                else{
                    elem = string[string.length()-1];
                    
                }
            }
        }
        if (!isCorrect(list)){
            std::cout << "The list isn't correct." << std::endl;
            in.close();
            out.close();
            return 1;
        }
        int i = 0;
        h_list.read_h_list(list,i);
        h_list.set_element(elem);
        in.close();

        h_list.browse(h_list.head);
        if (h_list.get_is_elem()){
            out << elem << " is found (" << h_list.get_number_elem() << " times)" << std::endl;
        }
        else{
            out << elem << " isn't found" << std::endl;
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