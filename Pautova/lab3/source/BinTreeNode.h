#ifndef BINTREENODE_H
#define BINTREENODE_H
#include <memory>

typedef char Elem;

class BinTreeNode{
public:
    Elem data;
    std::shared_ptr<BinTreeNode> left {nullptr};
    std::shared_ptr<BinTreeNode> right {nullptr};
};

#endif