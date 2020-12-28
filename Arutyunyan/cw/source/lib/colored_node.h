#ifndef COLORED_NODE_H_
#define COLORED_NODE_H_

#include "color.h"
#include "node.h"

template <typename T>
class ColoredNode {
 public:
  std::shared_ptr<Node<T>> node = nullptr;
  Color color = Color::kDefault;

  ColoredNode(std::shared_ptr<Node<T>> elem, Color color = Color::kDefault);
  template <typename TT>
  friend std::ostream& operator<<(std::ostream& out, ColoredNode<TT>& elem);
};

#include "colored_node.inl"

#endif  // COLORED_NODE_H_