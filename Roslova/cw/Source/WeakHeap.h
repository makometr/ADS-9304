#pragma once

#include <vector>
#include <memory>



class WeakHeap{
    bool isWeakHeap();
    void createWeakHeap();
    std::vector<bool> BIN;
    int binSize;
public:
    WeakHeap();
    void sortArr();
    std::vector<int> arr;
}; 