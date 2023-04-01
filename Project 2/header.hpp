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
    STNode() {
        int id;
        STNode* children[alphabetValues + 1];
        STNode* parent;
    }

};

class SuffixTree {
    public:
    STNode* buildNaiveTree();
    STNode* findPath(STNode*, std::string, int);
    
    private:
    STNode* root;
};

void readInputFile(std::string);
void readAlphabetFile(std::string);


#endif