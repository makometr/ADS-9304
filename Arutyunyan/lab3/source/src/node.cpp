#include "../lib/node.h"

Node::Node(std::variant<int, char, Operation> data,
           std::shared_ptr<Node> parent, std::shared_ptr<Node> left,
           std::shared_ptr<Node> right)
    : data_(data), left_(left), right_(right), parent_(parent) {}

bool Node::IsNumber() { return std::holds_alternative<int>(data_); }

bool Node::IsChar() { return std::holds_alternative<char>(data_); }

bool Node::IsOperation() { return std::holds_alternative<Operation>(data_); }

int Node::GetNumber() {
  if (!IsNumber()) {
    throw MyException(ErrorCode::kValueError, "Trying to get a different type");
  }
  return std::get<int>(data_);
}

char Node::GetChar() {
  if (!IsChar()) {
    throw MyException(ErrorCode::kValueError, "Trying to get a different type");
  }
  return std::get<char>(data_);
}

Operation Node::GetOperation() {
  if (!IsOperation()) {
    throw MyException(ErrorCode::kValueError, "Trying to get a different type");
  }
  return std::get<Operation>(data_);
}