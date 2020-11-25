#include "../lib/binary_tree.h"

using vector_traverse = std::vector<std::variant<int, char, Operation>>;

BinaryTree::BinaryTree(std::string_view str) {
  try {
    is_correct_binary_tree_ = true;
    CreateBinaryTree(str);
  } catch (MyException& err) {
    is_correct_binary_tree_ = false;
  }
}

BinaryTree::BinaryTree(const BinaryTree& object)
    : head_(nullptr), is_correct_binary_tree_(object.is_correct_binary_tree_) {
  if (object.head_ != nullptr) {
    head_ = std::shared_ptr<Node>(new Node(object.head_->data_));
    RecursiveCopy(head_, object.head_);
  }
}

BinaryTree::BinaryTree(BinaryTree&& object)
    : head_(std::move(object.head_)),
      is_correct_binary_tree_(std::move(object.is_correct_binary_tree_)) {}

BinaryTree& BinaryTree::operator=(const BinaryTree& object) {
  if (this == &object) {
    return *this;
  }
  is_correct_binary_tree_ = object.is_correct_binary_tree_;
  head_ = nullptr;
  if (object.head_ != nullptr) {
    head_ = std::shared_ptr<Node>(new Node(object.head_->data_));
    RecursiveCopy(head_, object.head_);
  }
  return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& object) {
  if (this == &object) {
    return *this;
  }
  is_correct_binary_tree_ = std::move(object.is_correct_binary_tree_);
  head_ = std::move(object.head_);
  return *this;
}

vector_traverse BinaryTree::InfixTraverse() {
  vector_traverse vec;
  RecursiveInfixTraverse(vec, head_);
  return vec;
}

vector_traverse BinaryTree::PrefixTraverse() {
  vector_traverse vec;
  RecursivePrefixTraverse(vec, head_);
  return vec;
}

vector_traverse BinaryTree::PostfixTraverse() {
  vector_traverse vec;
  RecursivePostfixTraverse(vec, head_);
  return vec;
}

bool BinaryTree::IsCorrectBinaryTree() { return is_correct_binary_tree_; }

void BinaryTree::Simplify() {
  if (is_correct_binary_tree_) {
    RecursiveSimplify(head_);
  }
}

void BinaryTree::CreateBinaryTree(std::string_view str) {
  int quantity_of_trees = 0;
  bool is_next_word = true;
  int index;
  std::shared_ptr<Node> curr = head_;
  for (index = 0; index < str.size(); ++index) {
    if (std::isspace(str[index])) {
      is_next_word = true;
      continue;
    } else if (!is_next_word) {
      throw MyException(ErrorCode::kSyntaxError, "invalid construction");
    } else if (!(std::isdigit(str[index]) || std::isalpha(str[index]) ||
                 IsOperation(str[index]))) {
      throw MyException(ErrorCode::kSyntaxError, "invalid symbol");
    } else if (IsOperation(str[index]) && quantity_of_trees <= 1) {
      throw MyException(ErrorCode::kSyntaxError,
                        "the operation was received too early");
    }

    bool is_operation = IsOperation(str[index]);

    if (!is_operation && !quantity_of_trees) {
      head_ = std::shared_ptr<Node>(new Node(ConvertToICO(str[index])));
      curr = head_;
      ++quantity_of_trees;

    } else if (!is_operation) {
      std::variant<int, char, Operation> var = Operation::kUnknown;
      auto temp = std::shared_ptr<Node>(new Node(var));
      temp->left_ = curr;
      temp->right_ = std::shared_ptr<Node>(new Node(ConvertToICO(str[index])));

      if (curr->parent_.expired()) {
        head_ = temp;
      } else {
        curr->parent_.lock()->right_ = temp;
      }

      temp->parent_ = curr->parent_;
      temp->left_->parent_ = temp;
      temp->right_->parent_ = temp;
      curr = temp->right_;
      ++quantity_of_trees;

    } else {
      curr->parent_.lock()->data_ = ToOperation(str[index]);
      curr = curr->parent_.lock();
      --quantity_of_trees;
    }

    is_next_word = false;
  }

  if (quantity_of_trees != 1) {
    throw MyException(ErrorCode::kSyntaxError, "invalid syntax");
  }
}

bool BinaryTree::IsOperation(const char c) {
  return c == '+' || c == '-' || c == '*';
}

Operation BinaryTree::ToOperation(const char c) {
  Operation oper;
  if (c == '+') {
    oper = Operation::kPlus;
  } else if (c == '-') {
    oper = Operation::kMinus;
  } else if (c == '*') {
    oper = Operation::kMultiply;
  } else {
    oper = Operation::kUnknown;
  }
  return oper;
}

void BinaryTree::RecursiveSimplify(std::shared_ptr<Node>& object) {
  if (object == nullptr) {
    return;
  }
  ToTryToReplace(object);
  RecursiveSimplify(object->left_);
  ToTryToReplace(object);
  RecursiveSimplify(object->right_);
  ToTryToReplace(object);
}

void BinaryTree::ToTryToReplace(std::shared_ptr<Node>& object) {
  if (object->IsOperation() && object->GetOperation() == Operation::kMinus &&
      object->left_->IsNumber() && object->right_->IsNumber()) {
    int diff = object->left_->GetNumber() - object->right_->GetNumber();
    if (diff < 0) {
      object->left_->data_ = 0;
      object->right_->data_ = -1 * diff;
    } else {
      object->data_ = diff;
      object->left_ = std::shared_ptr<Node>(nullptr);
      object->right_ = std::shared_ptr<Node>(nullptr);
    }
  }
}

std::variant<int, char, Operation> BinaryTree::ConvertToICO(const char c) {
  std::variant<int, char, Operation> variant;
  if (std::isdigit(c)) {
    variant = c - '0';
  } else if (IsOperation(c)) {
    variant = ToOperation(c);
  } else {
    variant = c;
  }
  return variant;
}

void BinaryTree::RecursiveInfixTraverse(vector_traverse& vec,
                                          std::shared_ptr<Node>& object) {
  if (object == nullptr) {
    return;
  }
  RecursiveInfixTraverse(vec, object->left_);
  vec.push_back(object->data_);
  RecursiveInfixTraverse(vec, object->right_);
}

void BinaryTree::RecursivePrefixTraverse(vector_traverse& vec,
                                           std::shared_ptr<Node>& object) {
  if (object == nullptr) {
    return;
  }
  vec.push_back(object->data_);
  RecursivePrefixTraverse(vec, object->left_);
  RecursivePrefixTraverse(vec, object->right_);
}

void BinaryTree::RecursivePostfixTraverse(vector_traverse& vec,
                                            std::shared_ptr<Node>& object) {
  if (object == nullptr) {
    return;
  }
  RecursivePostfixTraverse(vec, object->left_);
  RecursivePostfixTraverse(vec, object->right_);
  vec.push_back(object->data_);
}

void BinaryTree::RecursiveCopy(std::shared_ptr<Node>& curr_object,
                                 const std::shared_ptr<Node>& other_object) {
  if (other_object == nullptr) {
    return;
  }
  curr_object->left_ = nullptr;
  curr_object->right_ = nullptr;

  if (other_object->left_ != nullptr) {
    curr_object->left_ = std::shared_ptr<Node>(
        new Node(other_object->left_->data_, curr_object));
  }
  if (other_object->right_ != nullptr) {
    curr_object->right_ = std::shared_ptr<Node>(
        new Node(other_object->right_->data_, curr_object));
  }

  RecursiveCopy(curr_object->left_, other_object->left_);
  RecursiveCopy(curr_object->right_, other_object->right_);
}