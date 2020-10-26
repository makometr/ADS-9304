#include "node.h"

Node::Node (std::shared_ptr<Node> left, std::shared_ptr<Node> right, char data) : left(left), right(right), data(data) {}

std::ostream &operator<< (std::ostream &out, const std::shared_ptr<Node> cur) {
    if (cur->left)
        out << "(" << cur->left << cur->data << cur->right << ")";
    else
        out << cur->data;
    return out;
}
