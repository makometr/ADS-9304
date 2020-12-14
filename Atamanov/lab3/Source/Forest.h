//
// Created by neyther on 13.11.2020.
//

#ifndef LAB3_FOREST_H
#define LAB3_FOREST_H

#include <variant>
#include <algorithm>
#include <iostream>
#include <stack>
#include <cctype>

#include "BinTree.h"

std::string getConvenientLine(std::string::iterator iter) {
    std::string output;
    output.clear();
    while (*iter != '\0') {
        if (*iter != ' ')
            output.push_back(*iter);
        iter++;
    }
    return output;
}

void stringToVectorForest(std::string::iterator stringForest, std::vector <std::string> &forest) {
    std::stack<char> stack;
    int i = 0, j = 0;
    forest.resize(1);
    while (*stringForest != '\0') {
        if (*stringForest == '(') {
            stack.push(*stringForest);
            forest[i].push_back(*stringForest);
            j++;
        } else if (*stringForest == ')') {
            forest[i].push_back(*stringForest);
            stack.pop();
            if (stack.empty()) {
                if (*(stringForest + 1) != '\0') {
                    i++;
                    j = 0;
                    forest.resize(i + 1);
                }
                stringForest++;
                continue;
            }
        } else {
            forest[i].push_back(*stringForest);
            j++;
        }
        stringForest++;
    }
}

bool isCorrect(std::string::const_iterator &begin) {
    std::stack<char> Stack;
    if (*begin != '(') {
        return false;
    }
    for (; *begin != '\0'; begin++) {
        if (*begin == '(') {
            Stack.push(*begin);
        }
        if (*begin == ')') {
            if (Stack.empty()) {
                return false;
            }
            Stack.pop();
        }
    }
    return Stack.empty();
}

bool isEmpty(std::string::const_iterator& begin){
	for(begin;*begin!='\0';begin++)
		if(isalnum(*begin))
			return false;
	return true;
}	

template<typename T>
class Forest {
public:
    std::shared_ptr <Forest> next;
    std::shared_ptr <BinTreeNode<T>> tree;

    std::shared_ptr <Forest<T>> getForest(std::vector <std::string> forest) {
        if (forest.size()) {
            std::shared_ptr <Forest<T>> head = std::make_shared<Forest<T>>();
            std::shared_ptr <Forest<T>> temp = head;
            for (int i = 0; i < forest.size(); i++) {
                temp->tree = std::make_shared<BinTreeNode<T>>();
                temp->tree = std::make_shared<BinTreeNode<T>>();
                auto iterBeg = forest[i].cbegin();
                temp->tree = temp->tree->getBinTree(++iterBeg);
                if (i + 1 != forest.size()) {
                    temp->next = std::make_shared<Forest<T>>();
                    temp = temp->next;
                }
            }
            return head;
        } else
            return nullptr;
    }

    Forest() = default;

    void printForest(std::shared_ptr <Forest<T>> forest) {
        std::cout << "Forest\n";
        int level = 0;
        while (forest != nullptr) {
            tree->printForestBinTree(forest->tree, level);
            forest = forest->next;
        }
    }

    void widthSearch(std::shared_ptr <Forest<T>> forest) {
        std::cout << "Elements in horizontal search:\n";
        while (forest != nullptr) {
            forest->tree->widthSearch(forest->tree);
            forest = forest->next;
        }
        std::cout << "\n";
    }

};

#endif
