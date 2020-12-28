#pragma once

#include <vector>

class Node;

class Smootshort{
    std::vector<size_t> leonardo {};
    void createLeonardoNumbers(const unsigned sizeVec);
    bool isLeonardoNumbers(const size_t digit);
    void restoreHeap(std::shared_ptr<Node> &node);
public:
    void smootshort(std::vector<int> &sortVec);
    void radix(std::vector<int> digitArr);
};