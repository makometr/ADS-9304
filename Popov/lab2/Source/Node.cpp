#include "Node.h"



Node::Node(){
    next = nullptr;
}



Node::Node(std::variant<Node*, int> newValue){
    next = nullptr;
    value = newValue;
}




Node::~Node(){
    if(next)
    {
        delete next;
    }

    if(std::holds_alternative<Node*>(value))
    {
        delete std::get<Node*>(value);
    }
}



Node* Node::getNextPtr(){
    return next;
}



std::variant<Node*, int> Node::getValue(){
    return value;
}



void Node::setNextPtr(Node* newPtr){
    next = newPtr;
}



void Node::setValue(std::variant<Node*, int> newValue){
    value = newValue;
}