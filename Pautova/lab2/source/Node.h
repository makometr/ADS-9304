#ifndef NODE_H
#define NODE_H

#include <variant>

class Node{
public:
    Node * next;
    std::variant<Node*, char> value;
};

#endif