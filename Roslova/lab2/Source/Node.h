#pragma once

#include <memory>
#include <variant>



class Node{
    using NodePtr = std::shared_ptr<Node>;
public:
    Node();
    Node(char newValue);
    
    NodePtr next;
    std::variant<NodePtr, char> value;
};