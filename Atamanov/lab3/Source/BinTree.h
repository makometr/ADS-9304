#ifndef LAB3_BINTREE_H
#define LAB3_BINTREE_H

#include <memory>
#include <iostream>

template<typename T>
class Forest;

template<typename T>
class BinTreeNode {
public:
    std::shared_ptr <BinTreeNode> left{nullptr};
    std::shared_ptr <BinTreeNode> right{nullptr};
    T data;

    BinTreeNode() = default;

    ~BinTreeNode() = default;

    std::shared_ptr <BinTreeNode<T>> getBinTree(std::string::const_iterator &beg) {
        std::shared_ptr <BinTreeNode<T>> temp = std::make_shared<BinTreeNode<T>>();
        temp->data = *beg;
        bool left = true;
        beg++;
        while (1) {
            if (*beg == ')' && *(beg + 1) != '\0') {
                left = false;
                beg++;
            }
            if (*beg == ')' && left == false)
                break;
            if (*beg == '(' && left == true) {
                beg++;
                temp->left = getBinTree(beg);
            }
            if (*beg == '(') {
                beg++;
                temp->right = getBinTree(beg);
            }
            if (*beg == ')') {
                left = false;
            }
        }
        return temp;
    }

    std::shared_ptr <BinTreeNode<T>> convertForestToBinTree(std::shared_ptr <Forest<T>> &forest) {
        std::shared_ptr <BinTreeNode<T>> headBinTree;
        while (forest != nullptr) {
            headBinTree = std::make_shared<BinTreeNode<T>>();
            headBinTree = forest->tree;
            //temp->left = std::make_shared<BinTreeNode<T>>();
            if (forest->next != nullptr) {
                forest = forest->next;
                headBinTree->right = convertForestToBinTree(forest);
            }
            if (forest != nullptr)
                forest = forest->next;
        }
        return headBinTree;
    }

    std::shared_ptr <BinTreeNode<T>> copyTree(std::shared_ptr <BinTreeNode<T>> tree) {
        std::shared_ptr <BinTreeNode<T>> copyTree = std::make_shared<BinTreeNode<T>>();
        if (tree->left) {
            copyTree->left = std::make_shared<BinTreeNode<T>>();
            copyTree->left = copyTree(tree->left);
        }
        if (tree->right) {
            copyTree->right = std::make_shared<BinTreeNode<T>>();
            copyTree->right = copyTree(tree->right);
        }
    }

    void printForestBinTree(std::shared_ptr <BinTreeNode<T>> tree, int level) {
        for (int i = 0; i < level; i++)
            std::cout << "\t";
        std::cout << tree->data << "\n";
        if (tree->left)
            tree->printForestBinTree(tree->left, level + 1);
        if (tree->right)
            tree->printForestBinTree(tree->right, level);
    }

    void printBinTree(std::shared_ptr <BinTreeNode<T>> tree, int level) {
        //  std::cout << "BinTree:\n";
        for (int i = 0; i < level; i++)
            std::cout << "\t";
        std::cout << tree->data << "\n";
        if (tree->left)
            tree->printBinTree(tree->left, level + 1);
        if (tree->right)
            tree->printBinTree(tree->right, level + 1);
    }

    void widthSearch(std::shared_ptr <BinTreeNode<T>> tree) {
        std::cout << tree->data << " ";
        if (tree->left)
            tree->widthSearch(tree->left);
        if (tree->right)
            tree->widthSearch(tree->right);
    }
};

#endif //LAB3_BINTREE_H
