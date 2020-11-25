#pragma once
#include <iostream>
#include <memory>

class Node {

public:
    using NodePtr = std::shared_ptr<Node>;
    char value;
    NodePtr left;
    NodePtr right;
    Node();
    void printKLP(NodePtr head);
    bool isNull(NodePtr node);
    NodePtr consBT(const char& x, NodePtr, NodePtr);
    void printTree(std::shared_ptr<Node> node, int n);
    NodePtr copyTree(const NodePtr& head);
   // Node& operator=(const NodePtr& other);
    NodePtr moveTree(NodePtr &head);
    //Node(std::shared_ptr<Node> head);
};
