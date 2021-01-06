#ifndef TREAP_H_
#define TREAP_H_

#include <iomanip>
#include <memory>
#include <queue>
#include <random>
#include <sstream>
#include <vector>

#include "color.h"
#include "colored_node.h"
#include "node.h"

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
  std::shared_ptr<Node<T>> head_;
  Treap(std::shared_ptr<Node<T>> head);
  Treap<T>& operator=(Node<T>& tree);
  std::shared_ptr<Node<T>> InsertPrivate(std::shared_ptr<Node<T>> tree,
                                         std::shared_ptr<Node<T>> elem);
  void RemovePrivate(std::shared_ptr<Node<T>> tree, const T& key);
  std::shared_ptr<Node<T>> Split(std::shared_ptr<Node<T>> tree, const T& data);
  std::shared_ptr<Node<T>> Merge(std::shared_ptr<Node<T>> left,
                                 std::shared_ptr<Node<T>> right);
  size_t GetHeightPrivate(const std::shared_ptr<Node<T>> tree) const;
  std::vector<std::vector<std::shared_ptr<ColoredNode<T>>>> DumpFullBinaryTree()
      const;
  void RecursiveDumpFullBinaryTree(
      std::vector<std::vector<std::shared_ptr<ColoredNode<T>>>>& vec,
      std::shared_ptr<Node<T>> elem, long long current_level = 0) const;
  size_t RecursiveCount(std::shared_ptr<Node<T>> tree, const T& data) const;
  void PrintDataAndPriority(Color color, std::shared_ptr<Node<T>> elem) const;
  void PaintPartOfTree(
      std::vector<std::vector<std::shared_ptr<ColoredNode<T>>>> tree,
      std::shared_ptr<Node<T>> elem, Color color_vertex,
      Color color_other = Color::kDefault) const;
  size_t MaxLenghtOfElement() const;
  std::ostream& PrintFullBinaryTree(
      std::ostream& out,
      std::vector<std::vector<std::shared_ptr<ColoredNode<T>>>> tree) const;
  void PrintSeparator(Color color = Color::kPurple, int length = 175,
                      char separator = '-') const;
  void PrintAndPaintFullBinaryTree(std::shared_ptr<Node<T>> tree,
                                   Color color_vertex,
                                   Color color_other = Color::kDefault) const;
  void PrintRemoveInfo(const T& data) const;
  void PrintRemoveIfEqual(std::shared_ptr<Node<T>> tree) const;
  void PrintMerge(std::shared_ptr<Node<T>> tree) const;
};

#include "treap.inl"

#endif  // TREAP_H_
