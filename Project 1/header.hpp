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

void readInput(std::string filename);
void readConfig(std::string filename);
int getMaxOf3Int(int i, int s, int d);
void globalNeedlemanWunschAlgorithm(std::string*, std::string*);
int getMaxOrZero(int i, int s, int d);
void localSmithWatermanAlgorithm(std::string*, std::string*);

#endif