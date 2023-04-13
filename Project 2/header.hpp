#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <cmath>
#include <unordered_map>

#define ALPHABET_LENGTH 4

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
    STNode* children[ALPHABET_LENGTH + 1];
    STNode* parent;

    STNode () {
        id = 0;
        start = 0;
        end = 0;
        for (int i = 0; i < ALPHABET_LENGTH + 1; i++){
            children[i] = nullptr;
        }
        parent = nullptr;
    }

    STNode(int newID, STNode* newParent, int newStart, int newEnd) {
        id = newID;
        start = newStart;
        end = newEnd;
        for (int i = 0; i < ALPHABET_LENGTH + 1; i++){
            children[i] = nullptr;
        }
        parent = newParent;
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