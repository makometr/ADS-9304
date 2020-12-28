#include "colored_node.h"

template <typename T>
ColoredNode<T>::ColoredNode(std::shared_ptr<Node<T>> node_, Color color_)
    : node(node_), color(color_) {}

template <typename T>
std::ostream& operator<<(std::ostream& out, ColoredNode<T>& elem) {
  std::cout << elem.color;
  if (elem.node) {
    std::cout << elem.node->data_;
  } else {
    std::cout << '#';
  }
  std::cout << Color::kDefault;
  return out;
}