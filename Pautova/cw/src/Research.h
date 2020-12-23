#ifndef RESEARCH_H
#define RESEARCH_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <map>

#include "IBST.h"
#include "BST.h"

class Research{
public:
    void research_height(bool);
    void research_time(bool);

private:
    std::vector<int> generate_sequence(int size);
    std::vector<int> generate_randomseq(int size);
};

#endif