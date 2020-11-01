#pragma once

#include <variant>
#include <iostream>



class Node {
    std::variant <Node*, int> value;
    Node* next;
public:
    Node();
    Node(std::variant<Node*, int>);
    ~Node();
    Node* getNextPtr();
    std::variant<Node*, int> getValue();
    void setNextPtr(Node* newPtr);
    void setValue(std::variant<Node*, int> newValue);
};
