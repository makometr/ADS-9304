#ifndef __BINARYSEARCHTREE__H__
#define __BINARYSEARCHTREE__H__

#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include <vector>

#include "BinarySearchTreeNode.h"
#include "MyException.h"

template <typename T>
class BinarySearchTree
{
    std::shared_ptr<BinarySearchTreeNode<T>> head;

    std::shared_ptr<BinarySearchTreeNode<T>> min(const std::shared_ptr<BinarySearchTreeNode<T>> &ptrNode);
    void recursivePrefixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinarySearchTreeNode<T>> &nodePtr) const;
    void recursivePostfixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinarySearchTreeNode<T>> &nodePtr) const;
    void recursiveInfixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinarySearchTreeNode<T>> &nodePtr) const;
    void recursiveInsert(const T &val, std::shared_ptr<BinarySearchTreeNode<T>> &ptrNode, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent = nullptr);
    void recursiveRemove(const T &val, std::shared_ptr<BinarySearchTreeNode<T>> &ptrNode, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent = nullptr);
    std::shared_ptr<BinarySearchTreeNode<T>> recursiveCopy(const std::shared_ptr<BinarySearchTreeNode<T>> &ptrNodeToCopy, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent = nullptr);
    //для задания:
    bool checkTaskBin(const std::shared_ptr<BinarySearchTreeNode<T>> &ptrNode);
    std::shared_ptr<BinarySearchTreeNode<T>> recursiveConstructorFromStr(const std::string &str, std::shared_ptr<BinarySearchTreeNode<T>> &ptrNode, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent = nullptr);
    void recursiveSimplifyTheFormula(std::shared_ptr<BinarySearchTreeNode<T>> &ptrNode);
    void deleteSpaces(std::string &str);

    size_t curStrIndex = 0;

public:
    ~BinarySearchTree() = default;
    BinarySearchTree();
    BinarySearchTree(BinarySearchTree<T> &&tree);
    BinarySearchTree(const BinarySearchTree<T> &tree);
    BinarySearchTree<T> &operator=(BinarySearchTree<T> &&tree);
    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &tree);
    std::vector<T> prefixTraverse() const;
    std::vector<T> postfixTraverse() const;
    std::vector<T> infixTraverse() const;
    bool empty() const;
    void insert(const T &val);
    void remove(const T &val);

    template <typename C>
    friend std::ostream &operator<<(std::ostream &out, const BinarySearchTree<C> &bTree);

    //для задания:
    void simplifyTheFormula();
    BinarySearchTree(const std::string &str);
};

template <typename T>
void BinarySearchTree<T>::deleteSpaces(std::string &str)
{
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char sym) { return std::isspace(sym); }), str.end());
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &tree) : head(this->recursiveCopy(tree.head, nullptr)) {}

template <typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(const BinarySearchTree<T> &tree)
{
    if (this != &tree)
        this->head = this->recursiveCopy(tree.head, nullptr);
    return *this;
}

template <typename T>
std::shared_ptr<BinarySearchTreeNode<T>> BinarySearchTree<T>::recursiveCopy(const std::shared_ptr<BinarySearchTreeNode<T>> &ptrNodeToCopy, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent)
{
    if (ptrNodeToCopy != nullptr)
    {
        std::shared_ptr<BinarySearchTreeNode<T>> newObj(new BinarySearchTreeNode<T>(ptrNodeToCopy->obj, ptrParent));
        newObj->left = recursiveCopy(ptrNodeToCopy->left, newObj);
        newObj->right = recursiveCopy(ptrNodeToCopy->right, newObj);
        return newObj;
    }
    else
        return nullptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T> &&tree) : head(std::move(tree.head)) {}

template <typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(BinarySearchTree<T> &&tree)
{
    if (&tree != this)
        this->head = std::move(tree.head);
    return *this;
}

template <typename T>
void BinarySearchTree<T>::remove(const T &val)
{
    this->recursiveRemove(val, this->head);
}

template <typename T>
void BinarySearchTree<T>::recursiveRemove(const T &val, std::shared_ptr<BinarySearchTreeNode<T>> &ptrNode, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent)
{
    if (ptrNode != nullptr)
    {
        if (ptrNode->obj < val)
            recursiveRemove(val, ptrNode->right, ptrNode);
        else if (ptrNode->obj > val)
            recursiveRemove(val, ptrNode->left, ptrNode);
        else
        {
            std::shared_ptr<BinarySearchTreeNode<T>> ptrMin = nullptr;
            if (ptrNode->right != nullptr)
            {
                ptrMin = this->min(ptrNode->right);
                ptrMin->left = ptrNode->left;
                if (ptrMin->left != nullptr)
                    ptrMin->left->parent = ptrMin;
                if (ptrMin == ptrNode->right)
                    ptrMin->right = nullptr;
                else
                {
                    ptrMin->right = ptrNode->right;
                    ptrMin->right->parent = ptrMin;
                }
            }
            else if (ptrNode->left != nullptr)
            {
                ptrMin = ptrNode->left;
                ptrNode->left->parent = ptrMin;
            }
            if (ptrMin != nullptr)
            {
                if (ptrMin != ptrNode->right)
                    ptrMin->parent.lock()->left = nullptr;
                ptrMin->parent = ptrParent;
            }
            if (ptrParent != nullptr)
            {
                if (ptrParent->left == ptrNode)
                    ptrParent->left = ptrMin;
                else
                    ptrParent->right = ptrMin;
            }
            else
                this->head = ptrMin;
        }
    }
}

template <typename T>
std::shared_ptr<BinarySearchTreeNode<T>> BinarySearchTree<T>::min(const std::shared_ptr<BinarySearchTreeNode<T>> &ptrNode)
{
    std::shared_ptr<BinarySearchTreeNode<T>> ptr = ptrNode;
    if (ptrNode != nullptr)
    {
        while (ptr->left != nullptr)
            ptr = ptr->left;
    }
    return ptr;
}

template <typename T>
void BinarySearchTree<T>::insert(const T &val)
{
    this->recursiveInsert(val, this->head);
}

template <typename T>
void BinarySearchTree<T>::recursiveInsert(const T &val, std::shared_ptr<BinarySearchTreeNode<T>> &ptrNode, const std::shared_ptr<BinarySearchTreeNode<T>> &ptrParent)
{
    if (ptrNode == nullptr)
        ptrNode = std::shared_ptr<BinarySearchTreeNode<T>>(new BinarySearchTreeNode<T>(val, ptrParent));
    else if (val > ptrNode->obj)
        this->recursiveInsert(val, ptrNode->right, ptrNode);
    else if (val < ptrNode->obj)
        this->recursiveInsert(val, ptrNode->left, ptrNode);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const BinarySearchTree<T> &bTree)
{
    std::vector<T> vectorOfAtoms = bTree.prefixTraverse();
    for (auto it = vectorOfAtoms.begin(); it != vectorOfAtoms.end(); ++it)
    {
        if (it == vectorOfAtoms.begin())
            out << (*it);
        else
            out << ' ' << (*it);
    }
    return out;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
    this->head = std::unique_ptr<BinarySearchTreeNode<T>>(nullptr);
}

template class BinarySearchTree<char>;

template <>
void BinarySearchTree<char>::recursiveSimplifyTheFormula(std::shared_ptr<BinarySearchTreeNode<char>> &ptrNode)
{
    if (ptrNode != nullptr)
    {
        if (ptrNode->obj == '+')
        {
            ptrNode->obj = '*';
            ptrNode->left->obj = '2';
            ptrNode->left->left = nullptr;
            ptrNode->left->right = nullptr;
        }
        else
            recursiveSimplifyTheFormula(ptrNode->left);
        recursiveSimplifyTheFormula(ptrNode->right);
    }
}

template <>
void BinarySearchTree<char>::simplifyTheFormula()
{
    this->recursiveSimplifyTheFormula(this->head);
}

template <typename T>
void BinarySearchTree<T>::simplifyTheFormula()
{
    try
    {
        throw MyException(ExceptionsNames::ex_logic_error, "Using method with unsupported type");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

template <>
bool BinarySearchTree<char>::checkTaskBin(const std::shared_ptr<BinarySearchTreeNode<char>> &ptrNode)
{
    if (ptrNode != nullptr)
    {
        if (ptrNode->obj == '-' || ptrNode->obj == '+' || ptrNode->obj == '*' || ptrNode->obj == '/')
            return (ptrNode->left != nullptr && ptrNode->right != nullptr) ? checkTaskBin(ptrNode->left) && checkTaskBin(ptrNode->right) : 0;
        else if ((ptrNode->obj >= '0' && ptrNode->obj <= '9') || (ptrNode->obj >= 'a' && ptrNode->obj <= 'z'))
            return (ptrNode->left == nullptr && ptrNode->right == nullptr) ? 1 : 0;
        else
            return 0;
    }
    else
        return 1;
}

template <>
std::shared_ptr<BinarySearchTreeNode<char>> BinarySearchTree<char>::recursiveConstructorFromStr(const std::string &str, std::shared_ptr<BinarySearchTreeNode<char>> &ptrNode, const std::shared_ptr<BinarySearchTreeNode<char>> &ptrParent)
{
    char curObj = str[curStrIndex];
    ptrNode = std::shared_ptr<BinarySearchTreeNode<char>>(new BinarySearchTreeNode<char>(curObj, ptrParent));
    if (curStrIndex >= str.size())
        return nullptr;
    ++curStrIndex;
    if (curObj == '-' || curObj == '+' || curObj == '*' || curObj == '/')
    {
        ptrNode->left = recursiveConstructorFromStr(str, ptrNode->left, ptrNode);
        ptrNode->right = recursiveConstructorFromStr(str, ptrNode->right, ptrNode);
    }
    return ptrNode;
}

template <>
BinarySearchTree<char>::BinarySearchTree(const std::string &str)
{
    std::string newStr = str;
    if (!newStr.empty())
        this->deleteSpaces(newStr);
    this->head = this->recursiveConstructorFromStr(newStr, this->head);
    try
    {
        if (!this->checkTaskBin(this->head) || curStrIndex < newStr.size())
            throw MyException(ExceptionsNames::ex_syntax_error, "Wrong string");
    }
    catch (const std::exception &e)
    {
        this->head = nullptr;
        std::cerr << e.what() << '\n';
    }
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const std::string &str)
{
    try
    {
        throw MyException(ExceptionsNames::ex_logic_error, "Using method with unsupported type");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

template <typename T>
std::vector<T> BinarySearchTree<T>::prefixTraverse() const
{
    std::vector<T> vectorOfNodes;
    recursivePrefixTraverse(vectorOfNodes, this->head);
    return vectorOfNodes;
}

template <typename T>
std::vector<T> BinarySearchTree<T>::postfixTraverse() const
{
    std::vector<T> vectorOfNodes;
    recursivePostfixTraverse(vectorOfNodes, this->head);
    return vectorOfNodes;
}

template <typename T>
std::vector<T> BinarySearchTree<T>::infixTraverse() const
{
    std::vector<T> vectorOfNodes;
    recursiveInfixTraverse(vectorOfNodes, this->head);
    return vectorOfNodes;
}

template <typename T>
void BinarySearchTree<T>::recursivePrefixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinarySearchTreeNode<T>> &nodePtr) const
{
    if (nodePtr != nullptr)
    {
        vectorOfNodes.push_back(nodePtr->obj);
        this->recursivePrefixTraverse(vectorOfNodes, nodePtr->left);
        this->recursivePrefixTraverse(vectorOfNodes, nodePtr->right);
    }
}

template <typename T>
void BinarySearchTree<T>::recursivePostfixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinarySearchTreeNode<T>> &nodePtr) const
{
    if (nodePtr != nullptr)
    {
        this->recursivePostfixTraverse(vectorOfNodes, nodePtr->left);
        this->recursivePostfixTraverse(vectorOfNodes, nodePtr->right);
        vectorOfNodes.push_back(nodePtr->obj);
    }
}

template <typename T>
void BinarySearchTree<T>::recursiveInfixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinarySearchTreeNode<T>> &nodePtr) const
{
    if (nodePtr != nullptr)
    {
        this->recursiveInfixTraverse(vectorOfNodes, nodePtr->left);
        vectorOfNodes.push_back(nodePtr->obj);
        this->recursiveInfixTraverse(vectorOfNodes, nodePtr->right);
    }
}

template <typename T>
bool BinarySearchTree<T>::empty() const
{
    return (this->head == nullptr) ? 0 : 1;
}

#endif //!__BINARYSEARCHTREE__H__