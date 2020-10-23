#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include <vector>
#include "node.h"

class List {
public:
    List (std::vector<std::string>);
    ~List ();
    friend std::ostream &operator<< (std::ostream &, const List &);
    int connect (std::string, std::string);

private:
    Node *createNode (unsigned int);
    void deleteNode (Node *);
    Node *findNode (Node *, int *, int, int);
    void changeNum (Node *, int *, int);

    Node *head;
    std::vector<std::string> text;

};

#endif //LIST_H
