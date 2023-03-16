#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <cmath>
#include <unordered_map>

class STNode {
    public:
    STNode() {}
};

class SuffixTree {
    public:
    SuffixTree() {}

    private:
    STNode* root;
};

void readInputFile(std::string);
void readAlphabetFile(std::string);

#endif