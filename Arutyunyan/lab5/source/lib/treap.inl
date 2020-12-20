#include "treap.h"

template <typename T>
void Treap<T>::Insert(const T& data) {
  std::random_device rd;
  std::mt19937 mersenne_twister(rd());
  std::shared_ptr<Tree<T>> elem(new Tree<T>(data, mersenne_twister()));
  head_ = InsertPrivate(head_, elem);
}

template <typename T>
void Treap<T>::Remove(const T& data) {
  RemovePrivate(head_, data);
}

template <typename T>
size_t Treap<T>::Count(const T& data) const {
  return RecursiveCount(head_, data);
}

template <typename T>
size_t Treap<T>::GetHeight() const {
  return GetHeightPrivate(head_);
}

template <typename T>
size_t Treap<T>::CountAndThenInsert(const T& data) {
  size_t save_count = Count(data);
  Insert(data);
  return save_count;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Treap<T>& tree) {
  std::queue<std::shared_ptr<Tree<T>>> queue;
  const size_t height = tree.GetHeight();
  size_t element_length = 0;

  if (tree.head_ != nullptr) {
    queue.push(tree.head_);
  }

  while (!queue.empty()) {
    std::shared_ptr<Tree<T>> elem = queue.front();
    queue.pop();

    if (elem != nullptr) {
      std ::stringstream ss;
      ss << elem->data_;
      element_length = std::max(element_length, ss.str().size());

      queue.push(elem->left_);
      queue.push(elem->right_);
    }
  }

  auto vec = tree.DumpFullBinaryTree();

  for (int current_level = 0; current_level < height; ++current_level) {
    if (current_level) {
      out << '\n';
    }
    for (int i = 0; i < vec[current_level].size(); ++i) {
      size_t cell_width = height - current_level + 1;
      if (!i) {
        --cell_width;
      }
      out << std::setw((1 << cell_width) * element_length);
      if (vec[current_level][i] == nullptr) {
        out << '#';
      } else {
        out << vec[current_level][i]->data_;
      }
    }
  }
  return out;
}

template <typename T>
std::shared_ptr<Tree<T>> Treap<T>::InsertPrivate(
    std::shared_ptr<Tree<T>> tree, std::shared_ptr<Tree<T>> elem) {
  std::shared_ptr<Tree<T>> new_element(nullptr);
  if (tree == nullptr) {
    new_element = elem;
  } else if (elem->priority_ > tree->priority_) {
    new_element = Split(tree, elem->data_);
    elem->left_ = new_element->left_;
    elem->right_ = new_element->right_;
    new_element = elem;
  } else {
    if (elem->data_ < tree->data_) {
      tree->left_ = InsertPrivate(tree->left_, elem);
    } else {
      tree->right_ = InsertPrivate(tree->right_, elem);
    }
    new_element = tree;
  }
  return new_element;
}

template <typename T>
void Treap<T>::RemovePrivate(std::shared_ptr<Tree<T>> tree, const T& data) {
  if (tree == nullptr) {
    return;
  } else if (tree->data_ != data) {
    if (data < tree->data_) {
      if (tree->left_ != nullptr) {
        if (tree->left_->data_ != data) {
          RemovePrivate(tree->left_, data);
        } else {
          tree->left_ = Merge(tree->left_->left_, tree->left_->right_);
        }
      }

    } else {
      if (tree->right_ != nullptr) {
        if (tree->right_->data_ != data) {
          RemovePrivate(tree->right_, data);
        } else {
          tree->right_ = Merge(tree->right_->left_, tree->right_->right_);
        }
      }
    }
  } else {
    head_ = Merge(head_->left_, head_->right_);
  }
}

template <typename T>
std::shared_ptr<Tree<T>> Treap<T>::Split(std::shared_ptr<Tree<T>> tree,
                                         const T& data) {
  std::shared_ptr<Tree<T>> new_element(nullptr);
  if (tree == nullptr) {
    new_element.reset(new Tree<T>(nullptr, nullptr));
  } else if (data > tree->data_) {
    new_element = Split(tree->right_, data);
    tree->right_ = new_element->left_;
    new_element->left_ = tree;
  } else {
    new_element = Split(tree->left_, data);
    tree->left_ = new_element->right_;
    new_element->right_ = tree;
  }
  return new_element;
}

template <typename T>
std::shared_ptr<Tree<T>> Treap<T>::Merge(std::shared_ptr<Tree<T>> left,
                                         std::shared_ptr<Tree<T>> right) {
  std::shared_ptr<Tree<T>> new_element(nullptr);
  if (left == nullptr) {
    new_element = right;
  } else if (right == nullptr) {
    new_element = left;
  } else if (left->priority_ > right->priority_) {
    left->right_ = Merge(left->right_, right);
    new_element = left;
  } else {
    right->left_ = Merge(left, right->left_);
    new_element = right;
  }
  return new_element;
}

template <typename T>
size_t Treap<T>::GetHeightPrivate(const std::shared_ptr<Tree<T>> tree) const {
  if (tree == nullptr) {
    return 0;
  }
  return 1 + std::max(GetHeightPrivate(tree->left_),
                      GetHeightPrivate(tree->right_));
}

template <typename T>
std::vector<std::vector<std::shared_ptr<Tree<T>>>>
Treap<T>::DumpFullBinaryTree() const {
  std::vector<std::vector<std::shared_ptr<Tree<T>>>> vec(GetHeight());
  RecursiveDumpFullBinaryTree(vec, head_);
  return vec;
}

template <typename T>
void Treap<T>::RecursiveDumpFullBinaryTree(
    std::vector<std::vector<std::shared_ptr<Tree<T>>>>& vec,
    std::shared_ptr<Tree<T>> elem, long long current_level) const {
  if (current_level == vec.size()) {
    return;
  }

  vec[current_level].push_back(elem);

  RecursiveDumpFullBinaryTree(vec, elem == nullptr ? nullptr : elem->left_,
                              current_level + 1);
  RecursiveDumpFullBinaryTree(vec, elem == nullptr ? nullptr : elem->right_,
                              current_level + 1);
}

template <typename T>
size_t Treap<T>::RecursiveCount(std::shared_ptr<Tree<T>> tree,
                                const T& data) const {
  if (tree == nullptr) {
    return 0;
  }

  return (tree->data_ == data) + (tree->data_ > data
                                     ? RecursiveCount(tree->left_, data)
                                     : RecursiveCount(tree->right_, data));
}