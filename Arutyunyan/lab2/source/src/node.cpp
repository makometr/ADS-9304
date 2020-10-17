#include "../lib/node.h"

Node::Node(std::shared_ptr<HierarchicalList>& object)
    : next_(nullptr), object_(object) {}
Node::Node(const TypeOfObject& object) : next_(nullptr), object_(object) {}
Node::Node(const long long& object) : next_(nullptr), object_(object) {}

const HierarchicalList& Node::GetHierarchicalList() {
  if (!IsHierarchicalList()) {
    throw MyException(ErrorCode::kRuntimeError,
                      "getting a different type of object");
  }
  return *(std::get<std::shared_ptr<HierarchicalList>>(object_));
}

const std::shared_ptr<Node>& Node::GetNext() { 
  return next_; 
}

const TypeOfObject& Node::GetOperation() {
  if (!IsOperation()) {
    throw MyException(ErrorCode::kRuntimeError,
                      "getting a different type of object");
  }
  return std::get<TypeOfObject>(object_);
}

int Node::GetNumber() {
  if (!IsNumber()) {
    throw MyException(ErrorCode::kRuntimeError,
                      "getting a different type of object");
  }
  return std::get<long long>(object_);
}

bool Node::IsHierarchicalList() {
  return std::holds_alternative<std::shared_ptr<HierarchicalList>>(object_);
}

bool Node::IsOperation() {
  return std::holds_alternative<TypeOfObject>(object_) &&
         std::get<TypeOfObject>(object_) != TypeOfObject::kVariable;
}

bool Node::IsVariable() {
  return std::holds_alternative<TypeOfObject>(object_) &&
         std::get<TypeOfObject>(object_) == TypeOfObject::kVariable;
}

bool Node::IsNumber() { 
  return std::holds_alternative<long long>(object_);
}
