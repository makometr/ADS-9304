#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <memory>

class Node {
public:
    Node (std::shared_ptr<Node>, std::shared_ptr<Node>, char);
    friend std::ostream &operator<< (std::ostream &, const std::shared_ptr<Node>);

private:
    std::shared_ptr<Node> left, right;
    char data;
    friend class Tree;

};

#endif //NODE_H
