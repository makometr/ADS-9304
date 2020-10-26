#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <memory>
#include "node.h"

class Tree {
public:
    Tree (std::string &);
    friend std::ostream &operator<< (std::ostream &, const Tree &);
    void transform ();
    static bool checkString (std::string);
    static bool recursionCheck (std::string);

private:
    std::shared_ptr<Node> createNode (std::string);
    void transformNode (std::shared_ptr<Node>);
    bool cmp (std::shared_ptr<Node>, std::shared_ptr<Node>);
    std::shared_ptr<Node> root;

};

#endif //TREE_H
