#ifndef CW_BINTREENODE_H
#define CW_BINTREENODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <map>
#include <algorithm>

class BinTreeNode {
public:
    std::shared_ptr<BinTreeNode> left{nullptr};
    std::shared_ptr<BinTreeNode> right{nullptr};
    std::pair<std::string, int> data;

    std::shared_ptr<BinTreeNode>getShannonFanoTree(std::pair<std::string, int> stringWithWeight, std::map<char, int> usingSymbols, std::map<char, std::string> &codes, std::string code);

    std::shared_ptr<BinTreeNode> getHuffmanTree(std::pair<std::string, int> stringWithWeight, std::map<char, int> usingSymbols);

    std::shared_ptr<BinTreeNode> makeNode(std::shared_ptr<BinTreeNode> leftNode, std::shared_ptr<BinTreeNode> rightNode, std::pair<std::string, int> leftFutureNode, std::pair<std::string, int> rightFutureNode);
};

static bool HuffmanComparator1(std::pair<std::string, int> a1, std::pair<std::string, int> a2);

#endif //CW_BINTREENODE_H
