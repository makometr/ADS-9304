#include "node.h"

Node::Node (Node *left, Node *right, char data) : left(left), right(right), data(data) {}

std::ostream &operator<< (std::ostream &out, const Node *cur) {
    if (cur->left)
        out << "(" << cur->left << cur->data << cur->right << ")";
    else
        out << cur->data;
    return out;
}
