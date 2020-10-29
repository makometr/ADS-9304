#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#include "BinTree.h"

bool isCorrect(std::string tree);

int main(int argc, char** argv){
    Elem E;
    std::string tree;
    BinTree bin_tree;
    if (argc < 3){
        std::cout << "BinTree = ";
        getline(std::cin, tree);
        std::cout << "Element to search for: ";
        std::cin >> E;
        
    }
    else{
        std::ifstream in(argv[1]);
        if (!in.is_open()){
            std::cout << argv[1] << ": No such file or directory" << std::endl;
            return 1; 
        }
        std::string string;
        while(getline(in, string)){
            if (string.find('(') != std::string::npos){
                tree = string;
            }
            else{
                if (string.length() > 24){
                    std::cout << "More than 1 search item entered." << std::endl;
                    in.close();
                    return 1;
                }
                else{
                    E = string[string.length()-1];   
                }
            }
        }
        in.close();
    }
    if (!isCorrect(tree)){
        std::cout << "The bintree isn't correct." << std::endl;
        return 1;
    }
    bin_tree.set_E(E);
    bin_tree.read_tree(tree);
    bin_tree.back_tracking(bin_tree.get_head());

    if (argc == 3){
        std::ofstream out(argv[2]);
        if (!out.is_open()){
            std::cout << argv[2] << ": No such file or directory" << std::endl;
            return 1;
        }
        if (bin_tree.get_number_E()){
            out << E <<" is found (" << bin_tree.get_number_E() << " times)\n";
            out << "path length = " << bin_tree.get_min_path() << "\n";
        }
        else{
            out << E <<" isn't found\n";
            out << "path length = -1\n";
        }
        out.close();    
    }
    else{
        if (bin_tree.get_number_E()){
            std::cout << E <<" is found (" << bin_tree.get_number_E() << " times)\n";
            std::cout << "path length = " << bin_tree.get_min_path();
        }
        else{
            std::cout << E <<" isn't found\n";
            std::cout << "path length = -1\n";
        }
    }
    return 0;
}

bool isCorrect(std::string tree){
    if (tree[0] != '(')
        return false;
    std::stack<char> Stack;
    for (char i : tree){
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
    if (Stack.empty()){
        if (tree.find("((") == std::string::npos)
            return true;
    }        
    return false;
}