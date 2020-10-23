#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
public:
    Node (Node *, Node *, char);
    friend std::ostream &operator<< (std::ostream &, const Node *);

private:
    Node *left, *right;
    char data;
    friend class Tree;

};

#endif //NODE_H
