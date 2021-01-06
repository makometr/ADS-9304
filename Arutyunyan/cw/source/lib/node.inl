#include "node.h"

template <typename T>
Node<T>::Node() : priority_(0), right_(nullptr), left_(nullptr) {}

template <typename T>
Node<T>::Node(const T& data, long long priority, std::shared_ptr<Node<T>> left,
              std::shared_ptr<Node<T>> right)
    : data_(data), priority_(priority), left_(left), right_(right) {}

template <typename T>
Node<T>::Node(std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right)
    : priority_(0), left_(left), right_(right) {}