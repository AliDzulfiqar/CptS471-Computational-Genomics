#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

struct DP_Cell {
    int value;
    int direction;
    int sScore;
    int dScore;
    int iScore;
};

enum Direction {
    left = 0,
    diagonal = 1,
    up = 2
};

void readInputFile(std::string);
void readConfigFile(std::string);
int getMaxOf3Int(int, int, int);
int checkMatch(char a, char b);
int getMaxOrZero(int, int, int);
std::vector<std::vector<DP_Cell> > globalAlignment(std::string, std::string);
std::vector<std::vector<DP_Cell> > localAlignment(std::string, std::string);

#endif