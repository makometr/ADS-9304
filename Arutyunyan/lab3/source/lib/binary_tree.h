#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <vector>

#include "node.h"

class BinaryTree {
  using vector_traverse = std::vector<std::variant<int, char, Operation>>;

 public:
  BinaryTree() = default;
  BinaryTree(std::string_view str);
  BinaryTree(const BinaryTree& object);
  BinaryTree(BinaryTree&& object);

  BinaryTree& operator=(const BinaryTree& object);
  BinaryTree& operator=(BinaryTree&& object);

  vector_traverse InfixTraverse();
  vector_traverse PrefixTraverse();
  vector_traverse PostfixTraverse();

  bool IsCorrectBinaryTree();
  void Simplify();

  ~BinaryTree() = default;

 private:
  std::shared_ptr<Node> head_ = nullptr;
  bool is_correct_binary_tree_ = false;

  void CreateBinaryTree(std::string_view str);
  bool IsOperation(const char c);
  Operation ToOperation(const char c);
  void RecursiveSimplify(std::shared_ptr<Node>& object);
  void ToTryToReplace(std::shared_ptr<Node>& object);
  std::variant<int, char, Operation> ConvertToICO(const char c);

  void RecursiveInfixTraverse(vector_traverse& vec,
                              std::shared_ptr<Node>& object);
  void RecursivePrefixTraverse(vector_traverse& vec,
                               std::shared_ptr<Node>& object);
  void RecursivePostfixTraverse(vector_traverse& vec,
                                std::shared_ptr<Node>& object);
  void RecursiveCopy(std::shared_ptr<Node>& curr_object,
                     const std::shared_ptr<Node>& other_object);
};

#endif  // BINARY_TREE_H_