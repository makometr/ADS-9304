#ifndef TREE_H_
#define TREE_H_

#include <memory>

template <typename T>
class Treap;

template <typename T>
class Tree {
 public:
  Tree();
  Tree(const T& data, long long priority = 0,
       std::shared_ptr<Tree<T>> left = nullptr,
       std::shared_ptr<Tree<T>> right = nullptr);
  Tree(std::shared_ptr<Tree<T>> left, std::shared_ptr<Tree<T>> right);

 private:
  friend class Treap<T>;
  template <typename TT>
  friend std::ostream& operator<<(std::ostream& out, const Treap<TT>& tree);

  T data_;
  long long priority_;
  std::shared_ptr<Tree<T>> left_;
  std::shared_ptr<Tree<T>> right_;
};

#include "tree.inl"

#endif  // TREE_H_