#ifndef BINTREENODE_H
#define BINTREENODE_H
#include <memory>

template<typename Elem>
class BinTreeNode{
public:
    Elem data;
    std::shared_ptr<BinTreeNode<Elem>> left {nullptr};
    std::shared_ptr<BinTreeNode<Elem>> right {nullptr};
};

#endif