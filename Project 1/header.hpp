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
    int direction;

    DP_Cell(int s, int d, int i)
    {
        this->sScore = s;
        this->dScore = d;
        this->iScore = i;
    }

    DP_Cell()
    {
        this->sScore = 0;
        this->dScore = 0;
        this->iScore = 0;
    }
};



// void readInput(std::string);
// void readConfig(std::string);
int getMaxOf3Int(int, int, int);
int getMaxOrZero(int, int, int);
std::vector<std::vector<DP_Cell> > NeedlemanWunsch(std::string, std::string);

#endif