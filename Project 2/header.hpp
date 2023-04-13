#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <sys/sysctl.h>
#include <chrono>

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
    private:
        STNode* root;
    public:
    void setRootNode(STNode* newRoot) {
        root = newRoot;
    }
    STNode* getRootNode() {
        return root;
    };

    STNode* buildNaiveTree(std::string);
    STNode* findPath(std::string, int);
    std::string getPathLabel(std::string);
    STNode* nodeHops(std::string, std::string, int);
};

void readInputFile(std::string);
void readAlphabetFile(std::string);


#endif