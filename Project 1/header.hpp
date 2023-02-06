#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

struct DP_Cell {
    int sScore;
    int dScore;
    int iScore;

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

void readInput();
void readConfig();

#endif