#ifndef NODE_H_
#define NODE_H_

#include <memory>
#include <variant>

#include "my_exception.h"
#include "operation.h"

class Node {
 public:
  Node(std::variant<int, char, Operation> data,
       std::shared_ptr<Node> parent = nullptr,
       std::shared_ptr<Node> left = nullptr,
       std::shared_ptr<Node> right = nullptr);

  bool IsNumber();
  bool IsChar();
  bool IsOperation();
  int GetNumber();
  char GetChar();
  Operation GetOperation();
  ~Node() = default;

 private:
  friend class BinaryTree;
  std::variant<int, char, Operation> data_;
  std::shared_ptr<Node> left_ = nullptr;
  std::shared_ptr<Node> right_ = nullptr;
  std::weak_ptr<Node> parent_;
};

#endif  // NODE_H_