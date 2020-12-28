#ifndef CW_FUNCTIONS_H
#define CW_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <map>
#include <algorithm>
#include <cmath>

#include "BinTreeNode.h"

static bool HuffmanComparator(std::pair<std::string, int> a1, std::pair<std::string, int> a2);

void getListOfElem(std::map<char, int>& map, std::string::iterator iterator);

void getStringWithWeigh(std::map<char, int> stringMap, std::pair<std::string, int>& weightString);

void getCodesFromHuffman(std::shared_ptr<BinTreeNode> huffmanTree, std::map<char, std::string>& codesHuffman, std::string code);

void printTree(std::shared_ptr<BinTreeNode> tree, int level, std::string code, bool debug, bool left);

static bool HuffmanStringComparator(char a1, char a2);

void printHuffman(std::pair<std::string, int> stringWithWeight, std::map<char, int> usingSymbols, bool debug);

void printCodeTable(std::map<char, std::string> codes);

std::map<std::string, char> getCodesFromFile(const std::string& fileName);

void encode(std::string::iterator encodeString, std::string& shannonString, std::string& huffmanString, std::shared_ptr<BinTreeNode>& shannonTree, std::shared_ptr<BinTreeNode>& huffmanTree);


#endif //CW_FUNCTIONS_H
