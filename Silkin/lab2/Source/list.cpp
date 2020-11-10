#include "list.h"
#include <iostream>

List::List(std::string& str, char Old, char New){
    auto iter = str.begin();
    createList(&head, str, iter);
    print(head);
    std::cout << '\n';
    replaceElem(head, Old, New);
    print(head);
    std::cout << '\n';
}

void List::createList(Node**ptr, std::string& str, std::string::iterator& iter)
{
    if(iter < str.end()) {
        if(*iter == '(') {
            (*ptr)->value = new Node;
            iter++;
            if(*iter != ')') {
                createList(&(std::get<Node*>((*ptr)->value)), str, iter);
            } else {
                delete std::get<Node*>((*ptr)->value);
                (*ptr)->value = nullptr;
            }
        } else if(*iter == ')') {
            iter++;
            return;
        } else {
            Node* next_node = new Node;
            next_node->value = '\0';
            (*ptr)->next = next_node;
            (*ptr)->value = *iter;
            iter++;
            createList(&(*ptr)->next, str, iter);
        }
        if((*ptr)->next != nullptr)
            createList(&(*ptr)->next, str, iter);
    }
}

void List::print(Node *ptr) {
    Node* tmp = ptr;
    while (tmp != nullptr)
    {
        if(std::holds_alternative<Node*>(tmp->value)) {
            if(std::get<Node*>(tmp->value) != nullptr) {
                print(std::get<Node*>(tmp->value));
            }
        } else {
            std::cout << std::get<char>(tmp->value) << ' ';
        }
        tmp = tmp->next;
    }
}

void List::replaceElem(Node* ptr, char Old, char New) {
    Node* tmp = ptr;
    while (tmp != nullptr)
    {
        if(std::holds_alternative<Node*>(tmp->value)) {
            if(std::get<Node*>(tmp->value) != nullptr) {
                replaceElem(std::get<Node*>(tmp->value), Old, New);
            }
        } else {
            if(std::get<char>(tmp->value) == Old) {
                tmp->value = New;
            }
        }
        tmp = tmp->next;
    }
}

List::~List() {
    deliting(head);
}

void List::deliting(Node* to_delete) {
    if(std::holds_alternative<Node*>(to_delete->value)) {
        if(std::get<Node*>(to_delete->value) != nullptr) {
            deliting(std::get<Node*>(to_delete->value));
        }
    }
    if(to_delete->next != nullptr) {
        deliting(to_delete->next);
    }
    delete to_delete;
}