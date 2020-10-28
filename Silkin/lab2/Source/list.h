#pragma once
#include <variant>
#include <string>

struct Node {
    std::variant<Node*, char> value;
    Node* next = nullptr;
};

class List {
    Node* head = new Node;
    void createList(Node**, std::string&, std::string::iterator&);
public:
    List(std::string&,char,char);
    void print(Node*);
    void replaceElem(Node*,char,char);
    ~List();
    void deliting(Node*);
};