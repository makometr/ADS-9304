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

#ifdef DEMO_ON
#include <termios.h>
#include <unistd.h>

enum class Color
{
    kRED = 31,
    kGREEN = 32,
    kBLUE = 34
};

#endif //DEMO_ON

#include "BinaryTreeNode.h"

template <typename T>
class RandomBinarySearchTree
{
    std::shared_ptr<BinaryTreeNode<T>> head = nullptr;
    size_t __treeSize = 0;
    bool doubleData = 0;

#ifdef DEMO_ON
    std::vector<T> randomPermutation;
#endif //DEMO_ON

    std::shared_ptr<BinaryTreeNode<T>> merge(std::shared_ptr<BinaryTreeNode<T>> &ptrLeft, std::shared_ptr<BinaryTreeNode<T>> &ptrRight);
    void recursivePrefixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const;
    void recursivePostfixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const;
    void recursiveInfixTraverse(std::vector<T> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const;
    void recursiveInsert(const T &val, std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent = nullptr);
    void recursiveRemove(const T &val, std::shared_ptr<BinaryTreeNode<T>> &ptrNode);
    const size_t recursiveSize(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const;
    std::shared_ptr<BinaryTreeNode<T>> recursiveCopy(const std::shared_ptr<BinaryTreeNode<T>> &ptrNodeToCopy, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent = nullptr);
    void insertAtRoot(const T &val, std::shared_ptr<BinaryTreeNode<T>> &nodePtr, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent);
    void recursiveGetLevel(std::vector<std::shared_ptr<BinaryTreeNode<T>>> &vec, const std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const size_t &level, const size_t &curLevel) const;
    const size_t recursiveHeight(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const;
    void leftTreeRotate(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode);
    void rightTreeRotate(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode);
    const bool recursiveFind(const T &val, const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const;
#ifdef DEMO_ON
    void printWithColors(std::ostream &out, const std::vector<std::shared_ptr<BinaryTreeNode<T>>> &nodes, const std::vector<Color> &color) const;
    int getKey() const;
    void printRandomPermutation(std::ostream &out) const;
    void ptrPrefixTraverse(std::vector<std::shared_ptr<BinaryTreeNode<T>>> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const;

#endif //DEMO_ON
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
    const bool find(const T &val) const;
    bool empty() const;
    void erase();
    void insert(const T &val);
    void remove(const T &val);
    const bool findAndInsert(const T &val);

    template <typename C>
    friend std::ostream &operator<<(std::ostream &out, const RandomBinarySearchTree<C> &bTree);
};

#ifdef DEMO_ON

template <typename T>
void RandomBinarySearchTree<T>::ptrPrefixTraverse(std::vector<std::shared_ptr<BinaryTreeNode<T>>> &vectorOfNodes, const std::shared_ptr<BinaryTreeNode<T>> &nodePtr) const
{
    if (nodePtr != nullptr)
    {
        vectorOfNodes.push_back(nodePtr);
        this->ptrPrefixTraverse(vectorOfNodes, nodePtr->left);
        this->ptrPrefixTraverse(vectorOfNodes, nodePtr->right);
    }
}

template <typename T>
void RandomBinarySearchTree<T>::printRandomPermutation(std::ostream &out) const
{
    for (auto it = this->randomPermutation.begin(); it != this->randomPermutation.end(); ++it)
        out << *it << ' ';
}

template <typename T>
int RandomBinarySearchTree<T>::getKey() const
{
    int pressedKey = 0;
    termios oldt, newt; // oldt - состояние терминала до приема клавиши, newt - во время приема
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    pressedKey = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return pressedKey;
}

template <typename T>
void RandomBinarySearchTree<T>::printWithColors(std::ostream &out, const std::vector<std::shared_ptr<BinaryTreeNode<T>>> &nodes, const std::vector<Color> &colors) const
{
    std::vector<std::vector<std::shared_ptr<BinaryTreeNode<T>>>> vecOfDatasInCurrentLevel;
    const size_t h = this->height();
    size_t maxLen = 0;

    for (size_t currentLevel = 0; currentLevel < h; ++currentLevel)
    {
        vecOfDatasInCurrentLevel.push_back(this->getLevel(currentLevel));
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
            bool isColored = 0;
            for (size_t indexOfColoredNode = 0; indexOfColoredNode < nodes.size(); ++indexOfColoredNode)
                if (nodes[indexOfColoredNode] == *it)
                {
                    isColored = 1;
                    out << "\e[" << (int)colors[indexOfColoredNode] << "m";
                    break;
                }

            if (it == vecOfDatasInCurrentLevel[currentLevel].begin())
                out << std::setw((1 << (h - 1 - currentLevel)) * maxLen);
            else
                out << std::setw((1 << (h - currentLevel)) * maxLen);
            if (*it == nullptr)
                out << '#';
            else
            {
                out << (*it)->getData();
                if (isColored == 1)
                    out << "\e[0m";
            }
        }
    }
}
#endif //DEMO_ON

template <typename T>
void RandomBinarySearchTree<T>::erase()
{
    this->head = nullptr;
    this->__treeSize = 0;
}

template <typename T>
const bool RandomBinarySearchTree<T>::findAndInsert(const T &val)
{
#ifdef DEMO_ON
    std::cout << "Find and insert " << val << '\n';
#endif // DEMO_ON
    const bool cnt = this->find(val);
    this->insert(val);
    return cnt;
}

template <typename T>
RandomBinarySearchTree<T>::RandomBinarySearchTree(std::vector<T> elems)
{
#ifndef DEMO_ON
    std::random_shuffle(elems.begin(), elems.end());
    for (auto it = elems.begin(); it != elems.end(); ++it)
        this->insert(*it);
#endif

#ifdef DEMO_ON
    this->randomPermutation = elems;
    std::cout << "[CONSTRUCTOR] Your input: ";
    this->printRandomPermutation(std::cout);
    std::cout << '\n';
    std::cout << "Need to choose a random permutation. Press any key\n";
    this->getKey();
    std::random_shuffle(this->randomPermutation.begin(), this->randomPermutation.end());
    std::cout << "[CONSTRUCTOR] Random permutation: ";
    this->printRandomPermutation(std::cout);
    std::cout << '\n';
    std::cout << "The next step is to build a tree by inserting items from a random permutation. Press any key\n";
    this->getKey();
    system("clear");

    size_t sizeOfPermutation = this->randomPermutation.size();
    for (size_t it = 0; it < sizeOfPermutation; ++it)
    {
        this->insert(this->randomPermutation[it]);
    }
    std::cout << "[CONSTRUCTOR] Success\n"
              << *this << "\nPress any key to continue\n";
    this->getKey();
    system("clear");
#endif
}

template <typename T>
const bool RandomBinarySearchTree<T>::find(const T &val) const
{
    return this->recursiveFind(val, this->head);
}

template <typename T>
const bool RandomBinarySearchTree<T>::recursiveFind(const T &val, const std::shared_ptr<BinaryTreeNode<T>> &ptrNode) const
{
    if (ptrNode != nullptr)
    {
        if (ptrNode->getData() == val)
        {
#ifdef DEMO_ON
            std::cout << "Looking for " << val << " into the tree\n";
            std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
            nodesToColor.push_back(ptrNode);
            std::vector<Color> colors;
            colors.push_back(Color::kGREEN);
            this->printWithColors(std::cout, nodesToColor, colors);
            std::cout << "\n[FIND] Finded. Press any to continue\n";
            this->getKey();
            system("clear");
#endif // DEMO_ON
            return 1;
        }
        else if (ptrNode->getData() < val)
        {
#ifdef DEMO_ON
            std::cout << "Looking for " << val << " into the tree\n";
            std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
            nodesToColor.push_back(ptrNode);
            std::vector<Color> colors;
            colors.push_back(Color::kRED);
            this->printWithColors(std::cout, nodesToColor, colors);
            std::cout << "\n[FIND] No. Move to the right subtree because " << ptrNode->getData() << " < " << val << " . Press any to continue\n";
            this->getKey();
            system("clear");
#endif // DEMO_ON

            return this->recursiveFind(val, ptrNode->right);
        }
        else
        {
#ifdef DEMO_ON
            std::cout << "Looking for " << val << " into the tree\n";
            std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
            nodesToColor.push_back(ptrNode);
            std::vector<Color> colors;
            colors.push_back(Color::kRED);
            this->printWithColors(std::cout, nodesToColor, colors);
            std::cout << "\n[FIND] No. Move to the left subtree because " << ptrNode->getData() << " > " << val << " . Press any to continue\n";
            this->getKey();
            system("clear");
#endif // DEMO_ON

            return this->recursiveFind(val, ptrNode->left);
        }
    }
    else
    {
#ifdef DEMO_ON
        std::cout << "Looking for " << val << " into the tree\n";
        std::cout << *this;
        std::cout << "\n[FIND] No . Press any to continue\n";
        this->getKey();
        system("clear");
#endif // DEMO_ON
        return 0;
    }
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
#ifdef DEMO_ON
        std::cout << "[LEFT ROTATE] Rotating right subtree to left\n";
        std::cout << "The root of the \e[32mright\e[0m subtree, along with the lower part, must be inserted in place of the \e[34mcurrent root\e[0m.\nThe \e[34mprevious root\e[0m, along with its entire left subtree, must be attached to the new root on the left.\nThe \e[31mprevious left\e[0m subtree of the new root must be inserted to the root of the new left subtree (previous \e[34mcurrent root\e[0m) on the right.\n";
        std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodes;
        std::vector<Color> colors;
        if (ptrNode->right != nullptr)
        {
            this->ptrPrefixTraverse(nodes, ptrNode->right->right);
            nodes.push_back(ptrNode->right);
            for (size_t it = 0; it < nodes.size(); ++it)
                colors.push_back(Color::kGREEN);
            this->ptrPrefixTraverse(nodes, ptrNode->right->left);
            for (size_t it = colors.size(); it < nodes.size(); ++it)
                colors.push_back(Color::kRED);
        }
        nodes.push_back(ptrNode);
        colors.push_back(Color::kBLUE);
        this->printWithColors(std::cout, nodes, colors);
        std::cout << '\n';
        this->getKey();
#endif //DEMO_ON
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

#ifdef DEMO_ON
        std::cout << "[LEFT ROTATE] Success\n";
        this->printWithColors(std::cout, nodes, colors);
        std::cout << '\n';
        this->getKey();
        system("clear");
#endif //DEMO_ON
    }
}

template <typename T>
void RandomBinarySearchTree<T>::rightTreeRotate(const std::shared_ptr<BinaryTreeNode<T>> &ptrNode)
{
    if (ptrNode != nullptr)
    {
#ifdef DEMO_ON
        std::cout << "[RIGHT ROTATE] Rotating left subtree to right\n";
        std::cout << "The root of the \e[32mleft\e[0m subtree, along with the lower part, must be inserted in place of the \e[34mcurrent root\e[0m.\nThe \e[34mprevious root\e[0m, along with its entire right subtree, must be attached to the new root on the right.\nThe \e[31mprevious right\e[0m subtree of the new root must be inserted to the root of the new right subtree (previous \e[34mcurrent root\e[0m) on the left.\n";
        std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodes;
        std::vector<Color> colors;
        if (ptrNode->left != nullptr)
        {
            this->ptrPrefixTraverse(nodes, ptrNode->left->left);
            nodes.push_back(ptrNode->left);
            for (size_t it = 0; it < nodes.size(); ++it)
                colors.push_back(Color::kGREEN);
            this->ptrPrefixTraverse(nodes, ptrNode->left->right);
            for (size_t it = colors.size(); it < nodes.size(); ++it)
                colors.push_back(Color::kRED);
        }
        nodes.push_back(ptrNode);
        colors.push_back(Color::kBLUE);
        this->printWithColors(std::cout, nodes, colors);
        std::cout << '\n';
        this->getKey();
        system("clear");
#endif //DEMO_ON
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

#ifdef DEMO_ON
        std::cout << "[RIGHT ROTATE] Success\n";
        this->printWithColors(std::cout, nodes, colors);
        std::cout << '\n';
        this->getKey();
        system("clear");
#endif //DEMO_ON
    }
}

template <typename T>
const size_t RandomBinarySearchTree<T>::size() const
{
    return this->__treeSize;
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
void RandomBinarySearchTree<T>::recursiveRemove(const T &val, std::shared_ptr<BinaryTreeNode<T>> &ptrNode)
{
    if (ptrNode != nullptr)
    {
        if (ptrNode->getData() < val)
            recursiveRemove(val, ptrNode->right);
        else if (ptrNode->getData() > val)
            recursiveRemove(val, ptrNode->left);
        else
        {
            std::shared_ptr<BinaryTreeNode<T>> ptrParent = ptrNode->parent.lock();
            std::shared_ptr<BinaryTreeNode<T>> ptrTmp = this->merge(ptrNode->left, ptrNode->right);
            ptrNode->parent = ptrParent;
            if (ptrTmp == nullptr)
            {
                if (ptrParent != nullptr)
                {
                    if (ptrParent->right == ptrNode)
                        ptrParent->right = nullptr;
                    else
                        ptrParent->left = nullptr;
                }
                if (this->head == ptrNode)
                    this->head = nullptr;
            }
            ptrNode = ptrTmp;
            --(this->__treeSize);
        }
    }
}

template <typename T>
std::shared_ptr<BinaryTreeNode<T>> RandomBinarySearchTree<T>::merge(std::shared_ptr<BinaryTreeNode<T>> &ptrLeft, std::shared_ptr<BinaryTreeNode<T>> &ptrRight)
{
    std::shared_ptr<BinaryTreeNode<T>> ptrNode = nullptr;
    const size_t leftSize = (ptrLeft == nullptr) ? 0 : ptrLeft->size();
    const size_t rightSize = (ptrRight == nullptr) ? 0 : ptrRight->size();
    const size_t totalSize = leftSize + rightSize;
    if (totalSize != 0)
    {
        srand(clock());
        const size_t randNum = 1 + ((size_t)rand() % totalSize);
        if (randNum <= leftSize)
        {
            ptrNode = ptrLeft;
            ptrNode->right = merge(ptrNode->right, ptrRight);
        }
        else
        {
            ptrNode = ptrRight;
            ptrNode->left = merge(ptrLeft, ptrNode->left);
        }
    }
    return ptrNode;
}

template <typename T>
void RandomBinarySearchTree<T>::insert(const T &val)
{
#ifdef DEMO_ON
    std::cout << "Permutation: ";
    this->printRandomPermutation(std::cout);
    std::cout << '\n';
    std::cout << "Need to insert " << val << " into the";
    if (!(this->empty()))
        std::cout << " tree:\n"
                  << *this << '\n';
    else
        std::cout << " empty tree.";
    this->getKey();
    system("clear");
#endif //DEMO_ON
    this->recursiveInsert(val, this->head);
    this->doubleData = 0;
}

template <typename T>
void RandomBinarySearchTree<T>::recursiveInsert(const T &val, std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent)
{
    if (ptrNode == nullptr)
    {
        ptrNode = std::shared_ptr<BinaryTreeNode<T>>(new BinaryTreeNode<T>(val, ptrParent));
        ++(this->__treeSize);
#ifdef DEMO_ON
        std::cout << "Permutation: ";
        this->printRandomPermutation(std::cout);
        std::cout << '\n';
        std::cout << "Inserting " << val << " into the tree\n";
        std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
        std::vector<Color> colors;
        colors.push_back(Color::kGREEN);
        nodesToColor.push_back(ptrNode);
        this->printWithColors(std::cout, nodesToColor, colors);
        std::cout << "\n[INSERT] Inserted. Press any to continue\n";
        this->getKey();
        system("clear");
#endif //DEMO_ON
    }
    else
    {
        const size_t treeSize = this->size();
        srand(clock());
        const size_t randNum = 1 + (size_t)rand() % (treeSize + 1);

        if (randNum == treeSize + 1)
        {
#ifdef DEMO_ON
            std::cout << "[INSERT] Random number is " << randNum << " = " << treeSize + 1 << ". This means that the node will be inserted here by rotates\n";
#endif //DEMO_ON
            this->insertAtRoot(val, ptrNode, ptrParent);
        }
        else
        {
#ifdef DEMO_ON
            std::cout << "[INSERT] Random number is " << randNum << " != " << treeSize + 1 << '\n';
#endif //DEMO_ON
            if (ptrNode->getData() < val)
            {
#ifdef DEMO_ON

                std::cout << "Permutation: ";
                this->printRandomPermutation(std::cout);
                std::cout << '\n';
                std::cout << "Inserting " << val << " into the tree\n";
                std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
                std::vector<Color> colors;
                colors.push_back(Color::kRED);
                nodesToColor.push_back(ptrNode);
                this->printWithColors(std::cout, nodesToColor, colors);
                std::cout << "\n[INSERT] We move to the right subtree because " << val << " >= " << ptrNode->getData() << ". Press any to continue\n";
                this->getKey();
                system("clear");
#endif //DEMO_ON
                this->recursiveInsert(val, ptrNode->right, ptrNode);
            }
            else if (val < ptrNode->getData())
            {
#ifdef DEMO_ON
                std::cout << "Permutation: ";
                this->printRandomPermutation(std::cout);
                std::cout << '\n';
                std::cout << "Inserting " << val << " into the tree\n";
                std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
                std::vector<Color> colors;
                colors.push_back(Color::kRED);
                nodesToColor.push_back(ptrNode);
                this->printWithColors(std::cout, nodesToColor, colors);
                std::cout << "\n[INSERT] We move to the left subtree because " << val << " < " << ptrNode->getData() << ". Press any to continue\n";
                this->getKey();
                system("clear");
#endif //DEMO_ON
                this->recursiveInsert(val, ptrNode->left, ptrNode);
            }
#ifdef DEMO_ON
            else
            {
                std::cout << "[INSERT] " << val << " already exists in the tree\n";
                std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
                std::vector<Color> colors;
                colors.push_back(Color::kBLUE);
                nodesToColor.push_back(ptrNode);
                this->printWithColors(std::cout, nodesToColor, colors);
                this->getKey();
                system("clear");
            }
#endif
        }
    }
}

template <typename T>
void RandomBinarySearchTree<T>::insertAtRoot(const T &val, std::shared_ptr<BinaryTreeNode<T>> &ptrNode, const std::shared_ptr<BinaryTreeNode<T>> &ptrParent)
{
    if (ptrNode == nullptr)
    {
        ptrNode = std::shared_ptr<BinaryTreeNode<T>>(new BinaryTreeNode<T>(val, ptrParent));
        ++(this->__treeSize);
#ifdef DEMO_ON
        std::cout << "Permutation: ";
        this->printRandomPermutation(std::cout);
        std::cout << '\n';
        std::cout << "Inserting " << val << " into the tree\n";
        std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
        std::vector<Color> colors;
        colors.push_back(Color::kGREEN);
        nodesToColor.push_back(ptrNode);
        this->printWithColors(std::cout, nodesToColor, colors);
        std::cout << "\n[INSERT] Inserted. Press any to continue\n";
        this->getKey();
        system("clear");
#endif //DEMO_ON
    }
    else
    {
        if (ptrNode->getData() < val)
        {
#ifdef DEMO_ON
            std::cout << "Permutation: ";
            this->printRandomPermutation(std::cout);
            std::cout << '\n';
            std::cout << "Inserting " << val << " into the tree\n";
            std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
            std::vector<Color> colors;
            colors.push_back(Color::kRED);
            nodesToColor.push_back(ptrNode);
            this->printWithColors(std::cout, nodesToColor, colors);
            std::cout << "\n[INSERT] We move to the right subtree because " << val << " >= " << ptrNode->getData() << ". Press any to continue\n";
            this->getKey();
            system("clear");
#endif //DEMO_ON
            this->insertAtRoot(val, ptrNode->right, ptrNode);
            if (this->doubleData == 0)
                this->leftTreeRotate(ptrNode);
        }
        else if (val < ptrNode->getData())
        {
#ifdef DEMO_ON
            std::cout << "Permutation: ";
            this->printRandomPermutation(std::cout);
            std::cout << '\n';
            std::cout << "Inserting " << val << " into the tree\n";
            std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
            std::vector<Color> colors;
            colors.push_back(Color::kRED);
            nodesToColor.push_back(ptrNode);
            this->printWithColors(std::cout, nodesToColor, colors);
            std::cout << "\n[INSERT] We move to the left subtree because " << val << " < " << ptrNode->getData() << ". Press any to continue\n";
            this->getKey();
            system("clear");
#endif //DEMO_ON
            this->insertAtRoot(val, ptrNode->left, ptrNode);
            if (this->doubleData == 0)
                this->rightTreeRotate(ptrNode);
        }
        else
        {
            this->doubleData = 1;
#ifdef DEMO_ON
            std::cout << "[INSERT] " << val << " already exists in the tree\n";
            std::vector<std::shared_ptr<BinaryTreeNode<T>>> nodesToColor;
            std::vector<Color> colors;
            colors.push_back(Color::kBLUE);
            nodesToColor.push_back(ptrNode);
            this->printWithColors(std::cout, nodesToColor, colors);
            this->getKey();
            system("clear");
#endif
        }
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const RandomBinarySearchTree<T> &bTree)
{
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
    this->__treeSize = 0;
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
    return (this->head == nullptr) ? 1 : 0;
}

#endif //!__RANDOMBINARYSEARCHTREE__H__