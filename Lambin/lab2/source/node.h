#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <variant>

class Node {
public:
    Node (std::string, std::string, std::variant<std::string, Node *>, Node *);
    ~Node ();
    friend std::ostream &operator<< (std::ostream &, const Node *);

private:
    int *num;
    int count;
    std::string name;
    std::variant<std::string, Node *> data;
    Node *next;
    friend class List;

};

#endif //NODE_H
