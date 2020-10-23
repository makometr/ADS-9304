#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <memory>
#include <variant>

#include "my_exception.h"

enum class TypeOfObject {
  kPlus = 0,
  kMinus,
  kMultiply,
  kSqrt,
  kLog,
  kVariable
};

class HierarchicalList;

class Node {
 public:
  Node(std::shared_ptr<HierarchicalList>& object);
  Node(const TypeOfObject& object);
  Node(const long long& object);

  const HierarchicalList& GetHierarchicalList();
  const std::shared_ptr<Node>& GetNext();
  const TypeOfObject& GetOperation();
  int GetNumber();

  bool IsHierarchicalList();
  bool IsOperation();
  bool IsVariable();
  bool IsNumber();

  ~Node() = default;

 private:
  friend class HierarchicalList;
  std::shared_ptr<Node> next_;
  std::variant<std::shared_ptr<HierarchicalList>, TypeOfObject, long long>
      object_;
};
#endif  // NODE_H_