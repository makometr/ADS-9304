#ifndef __BINARYSEARCHTREENODE__H__
#define __BINARYSEARCHTREENODE__H__

#include <memory>

template <typename T>
class BinarySearchTree;

template <typename T>
class BinarySearchTreeNode
{
    friend class BinarySearchTree<T>;
    T obj;

public:
    std::shared_ptr<BinarySearchTreeNode<T>> left;
    std::shared_ptr<BinarySearchTreeNode<T>> right;
    std::weak_ptr<BinarySearchTreeNode<T>> parent;

    BinarySearchTreeNode(const T &val, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent = nullptr, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrLeft = nullptr, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrRight = nullptr);
};

template <typename T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(const T &val, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrLeft, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrRight) : obj(val), left(ptrLeft), right(ptrRight), parent(ptrParent) {}

#endif //!__BINARYSEARCHTREENODE__H__