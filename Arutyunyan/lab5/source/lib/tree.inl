#include "tree.h"

template <typename T>
Tree<T>::Tree() : priority_(0), right_(nullptr), left_(nullptr) {}

template <typename T>
Tree<T>::Tree(const T& data, long long priority, std::shared_ptr<Tree<T>> left,
              std::shared_ptr<Tree<T>> right)
    : data_(data), priority_(priority), left_(left), right_(right) {}

template <typename T>
Tree<T>::Tree(std::shared_ptr<Tree<T>> left, std::shared_ptr<Tree<T>> right)
    : priority_(0), left_(left), right_(right) {}