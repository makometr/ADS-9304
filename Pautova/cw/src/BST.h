#ifndef BINTREE_H
#define BINTREE_H

#include <string>
#include <vector>
#include <iostream>
#include <queue>

#include "BinTreeNode.h"

class BST{
public:
    BST(std::vector<int>&);
    ~BST() = default;

    BST(BST&& other);
    BST& operator=(BST&& other);

    BST(BST& other);
    BST& operator=(BST& other);
    std::shared_ptr<BinTreeNode<int>> copy(std::shared_ptr<BinTreeNode<int>>);
    
    void set_E(int E);
    
    void tracking(BST& cur);
    void printBST(std::shared_ptr<BinTreeNode<int>>&);
    void find(int E);
    void search(std::shared_ptr<BinTreeNode<int>>&);
    void insert(int data_to_insert);
    int height(std::shared_ptr<BinTreeNode<int>>&);
    std::shared_ptr<BinTreeNode<int>>& get_head();
    bool empty();
    
private:
    std::vector<int> sequence;
    int E;
    bool is_find = false;
    std::shared_ptr<BinTreeNode<int>> head;
    void make_tree(std::vector<int> tree);
};

#endif