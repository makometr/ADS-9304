#ifndef TREAP_H_
#define TREAP_H_

#include <iomanip>
#include <memory>
#include <queue>
#include <random>
#include <sstream>
#include <vector>

#include "tree.h"

template <typename T>
class Treap {
 public:
  Treap() = default;
  void Insert(const T& data);
  void Remove(const T& data);
  size_t Count(const T& data) const;
  size_t GetHeight() const;
  size_t CountAndThenInsert(const T& data);

  template <typename TT>
  friend std::ostream& operator<<(std::ostream& out, const Treap<TT>& tree);

  ~Treap() = default;

 private:
  std::shared_ptr<Tree<T>> head_;
  std::shared_ptr<Tree<T>> InsertPrivate(std::shared_ptr<Tree<T>> tree,
                                         std::shared_ptr<Tree<T>> elem);
  void RemovePrivate(std::shared_ptr<Tree<T>> tree, const T& key);
  std::shared_ptr<Tree<T>> Split(std::shared_ptr<Tree<T>> tree, const T& data);
  std::shared_ptr<Tree<T>> Merge(std::shared_ptr<Tree<T>> left, std::shared_ptr<Tree<T>> right);
  size_t GetHeightPrivate(const std::shared_ptr<Tree<T>> tree) const;
  std::vector<std::vector<std::shared_ptr<Tree<T>>>> DumpFullBinaryTree() const;
  void RecursiveDumpFullBinaryTree(std::vector<std::vector<std::shared_ptr<Tree<T>>>>& vec, std::shared_ptr<Tree<T>> elem, long long current_level = 0) const;
  size_t RecursiveCount(std::shared_ptr<Tree<T>> tree, const T& data) const;
};

#include "treap.inl"

#endif  // TREAP_H_
