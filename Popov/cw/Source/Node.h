#pragma once

#include <memory>


class Node{
public:
    Node(int newData);
    int data;
    size_t count;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};