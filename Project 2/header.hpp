#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <cmath>
#include <unordered_map>

/*
node u : suffix leaf i-1's parent

node v : suffix link SL(u)

node u': parent of u (if exists)

node v': SL(u') - may or may not be the parent of v
*/

class STNode {
    public:
    int id;
    int start;       
    int end;
    STNode* children;
    STNode* parent;

    STNode () {}

    STNode(int id, STNode* parent, int start, int end) {
        id = id;
        start = start;
        end = end
        children = nullptr;
        parent = parent;
    }
};

class SuffixTree {
    public:
    STNode* root;
    STNode* buildNaiveTree(std::string);
    STNode* findPath(STNode*, std::string, int);
};

void readInputFile(std::string);
void readAlphabetFile(std::string);


#endif