#ifndef __RANDOMBINARYSEARCHTREE__H__
#define __RANDOMBINARYSEARCHTREE__H__

#include <iostream>
#include <ostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <algorithm>

#include "BinaryTreeNode.h"
#include "MyException.h"

template <typename T>
class RandomBinarySearchTree
{
    std::shared_ptr<BinaryTreeNode<T>> head;

    std::shared_ptr<BinaryTreeNode<T>> merge(std::shared_ptr<BinaryTreeNode<T>> &ptrLeft, std::shared_ptr<BinaryTreeNode<T>> &ptrRight);
    void recursivePrefixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const;
    void recursivePostfixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const;
    void recursiveInfixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const;
    void recursiveInsert(const T &val, std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent = nullptr);
    void recursiveRemove(const T &val, std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent = nullptr);
    const size_t recursiveSize(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const;
    std::shared_ptr<BinaryTreeNode<T>> recursiveCopy(const std::shared_ptr<BinaryTreeNode<T>> &ptrNodeToCopy, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent = nullptr);
    void insertAtRoot(const T &val, std::shared_ptr<BinaryTreeNode<T>> &nodePtr, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent);
    void recursiveGetLevel(std::vector<std::shared_ptr<BinaryTreeNode<T>>> &vec, const std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const size_t &level, const size_t &curLevel) const;
    const size_t recursiveHeight(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const;
    void leftTreeRotate(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode);
    void rightTreeRotate(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode);
    const size_t recursiveFind(const T &val, const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const;

public:
    ~RandomBinarySearchTree() = default;
    RandomBinarySearchTree();
    RandomBinarySearchTree(std::vector<T> elems);
    RandomBinarySearchTree(RandomBinarySearchTree<T> &&tree);
    RandomBinarySearchTree(const RandomBinarySearchTree<T> &tree);
    RandomBinarySearchTree<T> &operator=(RandomBinarySearchTree<T> &&tree);
    RandomBinarySearchTree<T> &operator=(const RandomBinarySearchTree<T> &tree);
    const std::vector<T> prefixTraverse() const;
    const std::vector<T> postfixTraverse() const;
    const std::vector<T> infixTraverse() const;
    const std::vector<std::shared_ptr<BinaryTreeNode<T>>> getLevel(const size_t &level) const;
    const size_t size() const;
    const size_t height() const;
    const size_t find(const T &val) const;
    bool empty() const;
    void insert(const T &val);
    void remove(const T &val);
    const size_t taskFindAndInsert(const T &val);

    template <typename C>
    friend std::ostream &operator<<(std::ostream &out, const RandomBinarySearchTree<C> &bTree);
};

template <typename T>
const size_t RandomBinarySearchTree<T>::taskFindAndInsert(const T &val)
{
    const size_t cnt = this->find(val);
    this->insert(val);
    return cnt;
}

template <typename T>
RandomBinarySearchTree<T>::RandomBinarySearchTree(std::vector<T> elems)
{
    std::random_shuffle(elems.begin(), elems.end());
    for (auto it = elems.begin(); it != elems.end(); ++it)
        this->insert(*it);
}

template <typename T>
const size_t RandomBinarySearchTree<T>::find(const T &val) const
{
    return this->recursiveFind(val, this->head);
}

template <typename T>
const size_t RandomBinarySearchTree<T>::recursiveFind(const T &val, const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const
{
    if (ptrNode != nullptr)
        return ((ptrNode->getData() == val) ? 1 : 0) + this->recursiveFind(val, ptrNode->left) + this->recursiveFind(val, ptrNode->right);
    else
        return 0;
}

template <typename T>
const size_t RandomBinarySearchTree<T>::recursiveHeight(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const
{
    return (ptrNode != nullptr) ? (1 + std::max<size_t>(recursiveHeight(ptrNode->left), recursiveHeight(ptrNode->right))) : 0;
}

template <typename T>
const size_t RandomBinarySearchTree<T>::height() const
{
    return this->recursiveHeight(this->head);
}

template <typename T>
const std::vector<std::shared_ptr<BinaryTreeNode<T>>> RandomBinarySearchTree<T>::getLevel(const size_t &level) const
{
    std::vector<std::shared_ptr<BinaryTreeNode<T>>> vecOfDatas;
    this->recursiveGetLevel(vecOfDatas, this->head, level, 0);
    return vecOfDatas;
}

template <typename T>
void RandomBinarySearchTree<T>::recursiveGetLevel(std::vector<std::shared_ptr<BinaryTreeNode<T>>> &vec, const std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const size_t &level, const size_t &curLevel) const
{
    std::shared_ptr<BinaryTreeNode<T>> left = nullptr;
    std::shared_ptr<BinaryTreeNode<T>> right = nullptr;
    std::shared_ptr<BinaryTreeNode<T>> root = nullptr;
    if (ptrNode != nullptr)
    {
        left = ptrNode->left;
        right = ptrNode->right;
        root = ptrNode;
    }
    if (curLevel == level)
        vec.push_back(root);
    else
    {
        this->recursiveGetLevel(vec, left, level, curLevel + 1);
        this->recursiveGetLevel(vec, right, level, curLevel + 1);
    }
}

template <typename T>
void RandomBinarySearchTree<T>::leftTreeRotate(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode)
{
    if (ptrNode != nullptr)
    {
        std::shared_ptr<BinaryTreeNode<T>> newRoot = ptrNode->right;
        ptrNode->right = newRoot->left;
        if (ptrNode->right != nullptr)
            ptrNode->right->parent = ptrNode;
        newRoot->parent = ptrNode->parent;
        newRoot->left = ptrNode;
        newRoot->left->parent = newRoot;

        if (newRoot->parent.lock() != nullptr)
        {
            if (newRoot->parent.lock()->left == ptrNode)
                newRoot->parent.lock()->left = newRoot;

            if (newRoot->parent.lock()->right == ptrNode)
                newRoot->parent.lock()->right = newRoot;
        }
        if (ptrNode == this->head)
            this->head = newRoot;
    }
}

template <typename T>
void RandomBinarySearchTree<T>::rightTreeRotate(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode)
{
    if (ptrNode != nullptr)
    {
        std::shared_ptr<BinaryTreeNode<T>> newRoot = ptrNode->left;
        ptrNode->left = newRoot->right;
        if (ptrNode->left != nullptr)
            ptrNode->left->parent = ptrNode;
        newRoot->parent = ptrNode->parent;
        newRoot->right = ptrNode;
        newRoot->right->parent = newRoot;

        if (newRoot->parent.lock() != nullptr)
        {
            if (newRoot->parent.lock()->left == ptrNode)
                newRoot->parent.lock()->left = newRoot;

            if (newRoot->parent.lock()->right == ptrNode)
                newRoot->parent.lock()->right = newRoot;
        }
        if (ptrNode == this->head)
            this->head = newRoot;
    }
}

template <typename T>
const size_t RandomBinarySearchTree<T>::size() const
{
    return this->recursiveSize(this->head);
}

template <typename T>
const size_t RandomBinarySearchTree<T>::recursiveSize(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const
{
    return (ptrNode != nullptr) ? (1 + this->recursiveSize(ptrNode->left) + this->recursiveSize(ptrNode->right)) : 0;
}

template <typename T>
RandomBinarySearchTree<T>::RandomBinarySearchTree(const RandomBinarySearchTree<T> &tree) : head(this->recursiveCopy(tree.head, nullptr)) {}

template <typename T>
RandomBinarySearchTree<T> &RandomBinarySearchTree<T>::operator=(const RandomBinarySearchTree<T> &tree)
{
    if (this != &tree)
        this->head = this->recursiveCopy(tree.head, nullptr);
    return *this;
}

template <typename T>
std::shared_ptr<BinaryTreeNode<T>> RandomBinarySearchTree<T>::recursiveCopy(const std::shared_ptr<BinaryTreeNode<T>> &ptrNodeToCopy, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent)
{
    if (ptrNodeToCopy != nullptr)
    {
        std::shared_ptr<BinaryTreeNode<T>> newObj(new BinaryTreeNode<T>(ptrNodeToCopy->getData(), ptrParent));
        newObj->left = recursiveCopy(ptrNodeToCopy->left, newObj);
        newObj->right = recursiveCopy(ptrNodeToCopy->right, newObj);
        return newObj;
    }
    else
        return nullptr;
}

template <typename T>
RandomBinarySearchTree<T>::RandomBinarySearchTree(RandomBinarySearchTree<T> &&tree) : head(std::move(tree.head)) {}

template <typename T>
RandomBinarySearchTree<T> &RandomBinarySearchTree<T>::operator=(RandomBinarySearchTree<T> &&tree)
{
    if (&tree != this)
        this->head = std::move(tree.head);
    return *this;
}

template <typename T>
void RandomBinarySearchTree<T>::remove(const T &val)
{
    this->recursiveRemove(val, this->head);
}

template <typename T>
void RandomBinarySearchTree<T>::recursiveRemove(const T &val, std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent)
{
    if (ptrNode != nullptr)
    {
        if (ptrNode->getData() < val)
            recursiveRemove(val, ptrNode->right, ptrNode);
        else if (ptrNode->getData() > val)
            recursiveRemove(val, ptrNode->left, ptrNode);
        else
        {
            ptrNode = this->merge(ptrNode->left, ptrNode->right);
        }
    }
}

template <typename T>
std::shared_ptr<BinaryTreeNode<T>> RandomBinarySearchTree<T>::merge(std::shared_ptr<BinaryTreeNode<T>> &ptrLeft, std::shared_ptr<BinaryTreeNode<T>> &ptrRight)
{
    std::shared_ptr<BinaryTreeNode<T>> ptrNode = nullptr;
    const size_t leftSize = (ptrLeft != nullptr) ? ptrLeft->size() : 0;
    const size_t rightSize = (ptrRight != nullptr) ? ptrRight->size() : 0;
    const size_t totalSize = leftSize + rightSize;
    if (totalSize != 0)
    {
        srand(time(0));
        const size_t randNum = (size_t)rand() % totalSize;
        if (randNum < leftSize)
        {
            ptrNode = ptrLeft;
            ptrNode->right = merge(ptrNode->right, ptrRight);
        }
        else
        {
            ptrNode = ptrRight;
            ptrNode->right = merge(ptrNode->left, ptrLeft);
        }
    }
    return ptrNode;
}

template <typename T>
void RandomBinarySearchTree<T>::insert(const T &val)
{
    this->recursiveInsert(val, this->head);
}

template <typename T>
void RandomBinarySearchTree<T>::recursiveInsert(const T &val, std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent)
{
    if (ptrNode == nullptr)
        ptrNode = std::shared_ptr<BinaryTreeNode<T>>(new BinaryTreeNode<T>(val, ptrParent));
    else
    {
        const size_t treeSize = this->size();
        srand(time(0));
        const size_t randNum = 1 + (size_t)rand() % (treeSize + 1);

        if (randNum == treeSize + 1)
            this->insertAtRoot(val, ptrNode, ptrParent);
        else
        {
            if (ptrNode->getData() <= val)
                this->recursiveInsert(val, ptrNode->right, ptrNode);
            else if (val < ptrNode->getData())
                this->recursiveInsert(val, ptrNode->left, ptrNode);
        }
    }
}

template <typename T>
void RandomBinarySearchTree<T>::insertAtRoot(const T &val, std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent)
{
    if (ptrNode == nullptr)
        ptrNode = std::shared_ptr<BinaryTreeNode<T>>(new BinaryTreeNode<T>(val, ptrParent));
    else
    {
        if (ptrNode->getData() <= val)
        {
            this->insertAtRoot(val, ptrNode->right, ptrNode);
            this->leftTreeRotate(ptrNode);
        }
        if (val < ptrNode->getData())
        {
            this->insertAtRoot(val, ptrNode->left, ptrNode);
            this->rightTreeRotate(ptrNode);
        }
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const RandomBinarySearchTree<T> &bTree)
{
    out << "Tree:\n";
    std::vector<std::vector<std::shared_ptr<BinaryTreeNode<T>>>> vecOfDatasInCurrentLevel;
    const size_t h = bTree.height();
    size_t maxLen = 0;

    for (size_t currentLevel = 0; currentLevel < h; ++currentLevel)
    {
        vecOfDatasInCurrentLevel.push_back(bTree.getLevel(currentLevel));
        for (auto it = vecOfDatasInCurrentLevel[currentLevel].begin(); it != vecOfDatasInCurrentLevel[currentLevel].end(); ++it)
        {
            if ((*it) != nullptr)
            {
                std::ostringstream strToCheckLen;
                strToCheckLen << (*it)->getData();
                const size_t newLen = strToCheckLen.str().length();
                if (newLen > maxLen)
                    maxLen = newLen;
            }
        }
    }
    for (size_t currentLevel = 0; currentLevel < h; ++currentLevel)
    {
        if (currentLevel > 0)
            out << '\n';
        for (auto it = vecOfDatasInCurrentLevel[currentLevel].begin(); it != vecOfDatasInCurrentLevel[currentLevel].end(); ++it)
        {
            if (it == vecOfDatasInCurrentLevel[currentLevel].begin())
                out << std::setw((1 << (h - 1 - currentLevel)) * maxLen);
            else
                out << std::setw((1 << (h - currentLevel)) * maxLen);
            if (*it == nullptr)
                out << '#';
            else
                out << (*it)->getData();
        }
    }
    return out;
}

template <typename T>
RandomBinarySearchTree<T>::RandomBinarySearchTree()
{
    this->head = std::unique_ptr<BinaryTreeNode<T>>(nullptr);
}

template <typename T>
const std::vector<T> RandomBinarySearchTree<T>::prefixTraverse() const
{
    std::vector<T> vectorOfNodes;
    recursivePrefixTraverse(vectorOfNodes, this->head);
    return vectorOfNodes;
}

template <typename T>
const std::vector<T> RandomBinarySearchTree<T>::postfixTraverse() const
{
    std::vector<T> vectorOfNodes;
    recursivePostfixTraverse(vectorOfNodes, this->head);
    return vectorOfNodes;
}

template <typename T>
const std::vector<T> RandomBinarySearchTree<T>::infixTraverse() const
{
    std::vector<T> vectorOfNodes;
    recursiveInfixTraverse(vectorOfNodes, this->head);
    return vectorOfNodes;
}

template <typename T>
void RandomBinarySearchTree<T>::recursivePrefixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const
{
    if (nodePtr != nullptr)
    {
        vectorOfNodes.push_back(nodePtr->getData());
        this->recursivePrefixTraverse(vectorOfNodes, nodePtr->left);
        this->recursivePrefixTraverse(vectorOfNodes, nodePtr->right);
    }
}

template <typename T>
void RandomBinarySearchTree<T>::recursivePostfixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const
{
    if (nodePtr != nullptr)
    {
        this->recursivePostfixTraverse(vectorOfNodes, nodePtr->left);
        this->recursivePostfixTraverse(vectorOfNodes, nodePtr->right);
        vectorOfNodes.push_back(nodePtr->getData());
    }
}

template <typename T>
void RandomBinarySearchTree<T>::recursiveInfixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const
{
    if (nodePtr != nullptr)
    {
        this->recursiveInfixTraverse(vectorOfNodes, nodePtr->left);
        vectorOfNodes.push_back(nodePtr->getData());
        this->recursiveInfixTraverse(vectorOfNodes, nodePtr->right);
    }
}

template <typename T>
bool RandomBinarySearchTree<T>::empty() const
{
    return (this->head == nullptr) ? 0 : 1;
}

#endif //!__RANDOMBINARYSEARCHTREE__H__