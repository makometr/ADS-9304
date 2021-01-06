
#include "BinTreeNode.h"


static bool HuffmanComparator1(std::pair<std::string, int> a1, std::pair<std::string, int> a2){
    if(a1.second >= a2.second)
        return false;
    else
        return true;
}

std::shared_ptr<BinTreeNode> BinTreeNode::getShannonFanoTree(std::pair<std::string, int> stringWithWeight, std::map<char, int> usingSymbols, std::map<char, std::string>& codes, std::string code) {
    std::shared_ptr<BinTreeNode> tree = std::make_shared<BinTreeNode>();
    std::pair<std::string, int> left;
    std::pair<std::string, int> right;
    tree->data = stringWithWeight;
    if (stringWithWeight.first.length() == 1) {
        codes.insert({tree->data.first[0], code});
        return tree;
    }
    while (true) {
        if ((left.second + usingSymbols[stringWithWeight.first[0]]) > (stringWithWeight.second) && left.second == 0) {
            right.first += stringWithWeight.first[0];
            right.second += usingSymbols[stringWithWeight.first[0]];
            stringWithWeight.second -= usingSymbols[stringWithWeight.first[0]];
            stringWithWeight.first.erase(0, 1);
            left.first = stringWithWeight.first;
            left.second = stringWithWeight.second;
            break;
        } else if ((left.second + usingSymbols[stringWithWeight.first[0]]) > (stringWithWeight.second))
            break;
        else {
            left.first += stringWithWeight.first[0];
            left.second += usingSymbols[stringWithWeight.first[0]];
            stringWithWeight.second -= usingSymbols[stringWithWeight.first[0]];
            stringWithWeight.first.erase(0, 1);
        }
    }
    if (right.second == 0) {
        right.first = stringWithWeight.first;
        right.second = stringWithWeight.second;
    }

    if (left.second > right.second)
        std::swap(left, right);
    if (left.second != 0) {
        tree->left = std::make_shared<BinTreeNode>();
        tree->left = getShannonFanoTree(left, usingSymbols, codes, code + '0');
    }
    if (right.second != 0) {
        tree->right = std::make_shared<BinTreeNode>();
        tree->right = getShannonFanoTree(right, usingSymbols, codes, code + '1');
    }
    return tree;
}

std::shared_ptr<BinTreeNode> BinTreeNode::getHuffmanTree(std::pair<std::string, int> stringWithWeight, std::map<char, int> usingSymbols) {
    //Инициализация переменных
    std::shared_ptr<BinTreeNode> head; //Созданный узел
    std::map<std::string, std::shared_ptr<BinTreeNode>> tempNodes; //Мапа нераспределенных узлов
    std::map<std::string, int> tempLeft, tempRight; //Мапы левых и правых сыновей
    std::vector<std::pair<std::string, int>> huffmanString; // Основная строка с весами Хаффмана
    std::pair<std::string, int> temp, emptyPairLeft, emptyPairRight; // Текущая пара

    //Заполнение строки Хаффмана
    for (int i = 1; i <= stringWithWeight.first.length(); i++) {
        temp = std::make_pair(stringWithWeight.first[stringWithWeight.first.length() - i],
                              usingSymbols[stringWithWeight.first[stringWithWeight.first.length() - i]]);
        huffmanString.push_back(temp);
    }

    //Основной блок
    while (huffmanString.size() != 1) {

        //Если длина первых двух элементов равна по 1
        if (huffmanString[0].first.length() == 1 && huffmanString[1].first.length() == 1) {
            head = makeNode(nullptr, nullptr, huffmanString[0], huffmanString[1]);
            tempNodes.insert({huffmanString[0].first + huffmanString[1].first, head});
            temp = std::make_pair(huffmanString[0].first + huffmanString[1].first,
                                  huffmanString[0].second + huffmanString[1].second);
            huffmanString.erase(huffmanString.begin(), huffmanString.begin() + 2);
            huffmanString.push_back(temp);
            std::sort(huffmanString.begin(), huffmanString.end(), HuffmanComparator1);
        }

            //Если длина первого больше 1, а второго == 1
        else if (huffmanString[0].first.length() > 1 && huffmanString[1].first.length() == 1) {
            head = makeNode(tempNodes[huffmanString[0].first], nullptr, emptyPairLeft, huffmanString[1]);
            tempNodes.erase(huffmanString[1].first);
            tempNodes.insert({huffmanString[0].first + huffmanString[1].first, head});
            temp = std::make_pair(huffmanString[0].first + huffmanString[1].first,
                                  huffmanString[0].second + huffmanString[1].second);
            huffmanString.erase(huffmanString.begin(), huffmanString.begin() + 2);
            huffmanString.push_back(temp);
            std::sort(huffmanString.begin(), huffmanString.end(), HuffmanComparator1);
        }

            //Если длина первого - 1, а второго больше 1
        else if (huffmanString[0].first.length() == 1 && huffmanString[1].first.length() > 1) {
            head = makeNode(nullptr, tempNodes[huffmanString[1].first], huffmanString[0], emptyPairRight);
            tempNodes.erase(huffmanString[1].first);
            tempNodes.insert({huffmanString[0].first + huffmanString[1].first, head});
            temp = std::make_pair(huffmanString[0].first + huffmanString[1].first,
                                  huffmanString[0].second + huffmanString[1].second);
            huffmanString.erase(huffmanString.begin(), huffmanString.begin() + 2);
            huffmanString.push_back(temp);
            std::sort(huffmanString.begin(), huffmanString.end(), HuffmanComparator1);
        }

            //Если длина обоих больше 1
        else {
            head = makeNode(tempNodes[huffmanString[0].first], tempNodes[huffmanString[1].first], emptyPairLeft,
                            emptyPairRight);
            tempNodes.erase(huffmanString[0].first);
            tempNodes.erase(huffmanString[1].first);
            tempNodes.insert({huffmanString[0].first + huffmanString[1].first, head});
            temp = std::make_pair(huffmanString[0].first + huffmanString[1].first,
                                  huffmanString[0].second + huffmanString[1].second);
            huffmanString.erase(huffmanString.begin(), huffmanString.begin() + 2);
            huffmanString.push_back(temp);
            std::sort(huffmanString.begin(), huffmanString.end(), HuffmanComparator1);
        }
    }
    return head;
}

std::shared_ptr<BinTreeNode> BinTreeNode::makeNode(std::shared_ptr<BinTreeNode> leftNode, std::shared_ptr<BinTreeNode> rightNode, std::pair<std::string, int> leftFutureNode, std::pair<std::string, int> rightFutureNode) {
    std::shared_ptr<BinTreeNode> node = std::make_shared<BinTreeNode>();
    std::pair<std::string, int> empty;
    std::string temp;
    if (leftNode && rightNode) {
        node->left = leftNode;
        node->right = rightNode;
        node->data.first = node->left->data.first + node->right->data.first;
        node->data.second = node->left->data.second + node->right->data.second;
        return node;
    }
    if (leftNode && rightFutureNode.second != 0) {
        node->left = leftNode;
        node->right = makeNode(nullptr, nullptr, empty, rightFutureNode);
        node->data.first = node->left->data.first + node->right->data.first;
        node->data.second = node->left->data.second + node->right->data.second;
        return node;
    }
    if (leftFutureNode.second != 0 && rightNode) {
        node->left = makeNode(nullptr, nullptr, leftFutureNode, empty);
        node->right = rightNode;
        node->data.first = node->left->data.first + node->right->data.first;
        node->data.second = node->left->data.second + node->right->data.second;
        return node;
    }
    if (leftFutureNode.second != 0 && rightFutureNode.second != 0) {
        node->left = makeNode(nullptr, nullptr, leftFutureNode, empty);
        node->right = makeNode(nullptr, nullptr, empty, rightFutureNode);
        node->data.first = node->left->data.first + node->right->data.first;
        node->data.second = node->left->data.second + node->right->data.second;
        return node;
    }
    if (leftFutureNode.second != 0) {
        node->data.first = leftFutureNode.first;
        node->data.second = leftFutureNode.second;
        return node;
    }
    if (rightFutureNode.second != 0) {
        node->data.first = rightFutureNode.first;
        node->data.second = rightFutureNode.second;
        return node;
    }
}