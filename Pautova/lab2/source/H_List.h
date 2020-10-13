#ifndef H_LIST_H
#define H_LIST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <variant>

#include "Node.h"

class H_List{
    char elem;
    bool is_elem;
public:
    Node* head;

    void set_element(char elem);
    char get_is_elem();
    Node* read_node(std::string& list, int& i);
    void read_h_list(std::string& list, int& i);
    void print(Node* cur);
    void browse(Node* cur);
    void free_list(Node* cur);
};

#endif