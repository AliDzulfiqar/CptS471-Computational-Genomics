#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

struct DP_Cell {
    int sScore;
    int dScore;
    int iScore;
};

int checkMatch(char a, char b);

// void readInput(std::string);
// void readConfig(std::string);
int getMaxOf3Int(int, int, int);
int getMaxOrZero(int, int, int);

#endif