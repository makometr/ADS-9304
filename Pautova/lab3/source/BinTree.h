#ifndef BINTREE_H
#define BINTREE_H

#include <string>
#include <stack>
#include <vector>
#include <memory>
#include <iostream>

#include "BinTreeNode.h"

class BinTree{
public:
    BinTree() = default;
    ~BinTree() = default;

    BinTree(BinTree&& other);
    BinTree& operator=(BinTree&& other);

    BinTree(BinTree& other);
    BinTree& operator=(BinTree& other);
    std::shared_ptr<BinTreeNode> copy(std::shared_ptr<BinTreeNode> cur);
    
    void set_E(Elem E);

    void read_tree(std::string& tree);
    

    void printBinTree(std::shared_ptr<BinTreeNode> cur);
    void back_tracking(std::shared_ptr<BinTreeNode> cur); //обход ЛКП
    void insert(Elem data_to_insert);

    std::shared_ptr<BinTreeNode> get_head();
    int get_number_E();
    int get_min_path();

private:
    std::shared_ptr<BinTreeNode> read_node(std::string& tree);
    Elem E;
    int number_E;
    int path;
    std::vector<int> paths;
    std::shared_ptr<BinTreeNode> head;
};

#endif