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

    template <typename C>
    friend bool operator==(const BinarySearchTreeNode<C> &left, const BinarySearchTreeNode<C> &right);
    BinarySearchTreeNode(const T &val, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent = nullptr, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrLeft = nullptr, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrRight = nullptr);
};

template <typename T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(const T &val, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrLeft, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrRight) : obj(val), left(ptrLeft), right(ptrRight), parent(ptrParent) {}

template <typename C>
bool operator==(const BinarySearchTreeNode<C> &left, const BinarySearchTreeNode<C> &right)
{
    if (left.obj != right.obj)
        return 0;
    else
    {
        if ((left.left == nullptr || right.left == nullptr) && right.left != left.left)
            return 0;
        else
        {
            if ((left.right == nullptr || right.right == nullptr) && right.right != left.right)
                return 0;
            else
            {
                if (left.left != nullptr && left.right == nullptr)
                    return *(left.left) == *(right.left);
                else if (left.left == nullptr && left.right != nullptr)
                    return *(left.right) == *(right.right);
                else if (left.left != nullptr && left.right != nullptr)
                    return *(left.right) == *(right.right) && *(left.left) == *(right.left);
                else
                    return 1;
            }
        }
    }
}
#endif //!__BINARYSEARCHTREENODE__H__