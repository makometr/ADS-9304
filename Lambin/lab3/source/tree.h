#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <memory>
#include "node.h"

class Tree {
public:
    Tree (std::string &);
    Tree (const Tree &);
    Tree (Tree &&);
    Tree &operator = (const Tree &);
    Tree &operator = (Tree &&);
    friend std::ostream &operator<< (std::ostream &, const Tree &);
    void transform ();
    static bool checkString (std::string);
    static bool recursionCheck (std::string);

private:
    std::shared_ptr<Node> createNode (std::string);
    std::shared_ptr<Node> copyNode (std::shared_ptr<Node>);
    void transformNode (std::shared_ptr<Node>);
    bool cmp (std::shared_ptr<Node>, std::shared_ptr<Node>);
    std::shared_ptr<Node> root;

};

#endif //TREE_H
