#ifndef __BINARYTREENODE__H__
#define __BINARYTREENODE__H__

#include <memory>

template <typename T>
class RandomBinarySearchTree;

template <typename T>
class BinaryTreeNode
{
    friend class RandomBinarySearchTree<T>;
    T data;
    std::shared_ptr<BinaryTreeNode<T>> left;
    std::shared_ptr<BinaryTreeNode<T>> right;
    std::weak_ptr<BinaryTreeNode<T>> parent;

    const size_t recursiveSize(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const;

public:
    BinaryTreeNode(const T &val, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent = nullptr, const std::shared_ptr<BinaryTreeNode<T>> &ptrLeft = nullptr, const std::shared_ptr<BinaryTreeNode<T>> &ptrRight = nullptr);
    const size_t size() const;
    const T getData() const;
    template <typename C>
    friend bool operator==(const BinaryTreeNode<C> &left, const BinaryTreeNode<C> &right);

    BinaryTreeNode(BinaryTreeNode<T> &&toMove);
    BinaryTreeNode(const BinaryTreeNode<T> &toCopy);
    BinaryTreeNode<T> &operator=(BinaryTreeNode<T> &&toMove);
    BinaryTreeNode<T> &operator=(const BinaryTreeNode<T> &toMove);

    template <typename C>
    friend std::ostream &operator<<(std::ostream &out, const BinaryTreeNode<C> &right);
};

template <typename T>
BinaryTreeNode<T> &BinaryTreeNode<T>::operator=(const BinaryTreeNode<T> &toMove)
{
    if (this != &toMove)
    {
        this->data = toMove->data;
        this->left = toMove->left;
        this->right = toMove->right;
        this->parent = toMove->parent;
    }
    return *this;
}

template <typename T>
BinaryTreeNode<T> &BinaryTreeNode<T>::operator=(BinaryTreeNode<T> &&toMove)
{
    if (this != &toMove)
    {
        this->data = toMove->data;
        this->left = toMove->left;
        this->right = toMove->right;
        this->parent = toMove->parent;
        toMove->left = nullptr;
        toMove->right = nullptr;
        toMove->parent = nullptr;
    }
    return *this;
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(BinaryTreeNode<T> &&toMove)
{
    this->data = toMove->data;
    this->left = toMove->left;
    this->right = toMove->right;
    this->parent = toMove->parent;
    toMove->left = nullptr;
    toMove->right = nullptr;
    toMove->parent = nullptr;
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T> &toCopy)
{
    this->data = toCopy->data;
    this->left = toCopy->left;
    this->right = toCopy->right;
    this->parent = toCopy->parent;
}

template <typename T>
const size_t BinaryTreeNode<T>::size() const
{
    return (1 + this->recursiveSize(this->left) + this->recursiveSize(this->right));
}

template <typename T>
const size_t BinaryTreeNode<T>::recursiveSize(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const
{
    return (ptrNode != nullptr) ? (1 + this->recursiveSize(ptrNode->left) + this->recursiveSize(ptrNode->right)) : 0;
}

template <typename C>
std::ostream &operator<<(std::ostream &out, const BinaryTreeNode<C> &right)
{
    out << right.data;
    return out;
}

template <typename T>
const T BinaryTreeNode<T>::getData() const
{
    return this->data;
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T &val, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent, const std::shared_ptr<BinaryTreeNode<T>> &ptrLeft, const std::shared_ptr<BinaryTreeNode<T>> &ptrRight) : data(val), left(ptrLeft), right(ptrRight), parent(ptrParent) {}

template <typename C>
bool operator==(const BinaryTreeNode<C> &left, const BinaryTreeNode<C> &right)
{
    if (left.data != right.data)
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

#endif //!__BINARYTREENODE__H__