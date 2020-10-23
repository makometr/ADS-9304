#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include "node.h"

class Tree {
public:
    Tree (std::string &);
    ~Tree ();
    friend std::ostream &operator<< (std::ostream &, const Tree &);
    void transform ();
    static bool checkString (std::string);
    static bool recursionCheck (std::string);

private:
    Node *createNode (std::string);
    void deleteNode (Node *);
    void transformNode (Node *);
    bool cmp (Node *, Node *);
    Node *root;

};

#endif //TREE_H
