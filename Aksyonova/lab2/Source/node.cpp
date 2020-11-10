#include "node.h"
 
Node::Node(Node* next, std::variant<Node*, char> data): next(next), data(data) {
}
Node::~Node() {
}
