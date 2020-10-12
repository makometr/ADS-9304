#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include "node.h"

class List {
public:
    List (std::string *, unsigned int);
    ~List ();
    friend std::ostream &operator<< (std::ostream &, const List &);
    int connect (std::string, std::string);

private:
    Node *createNode (unsigned int);
    void deleteNode (Node *);
    Node *findNode (Node *, int *, int, int);
    void changeNum (Node *, int *, int);

    Node *head;
    std::string *text;
    unsigned int size;

};

#endif //LIST_H
