#ifndef TREE_H_
#define TREE_H_

#include <memory>

template <typename T>
class Treap;

template <typename T>
class Node {
 public:
  Node();
  Node(const T& data, long long priority = 0,
       std::shared_ptr<Node<T>> left = nullptr,
       std::shared_ptr<Node<T>> right = nullptr);
  Node(std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right);

 private:
  friend class Treap<T>;

  T data_;
  long long priority_;
  std::shared_ptr<Node<T>> left_;
  std::shared_ptr<Node<T>> right_;
};

#include "node.inl"

#endif  // TREE_H_