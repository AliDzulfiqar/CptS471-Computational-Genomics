#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

struct DP_Cell {
    int value;
    int cases;
    int sScore;
    int dScore;
    int iScore;
};

// enumerate cases
enum Case {
    insertion = 0,
    substitution = 1,
    deletion = 2
};

void readInputFile(std::string);
void readConfigFile(std::string);
int getMaxOf3Int(int, int, int);
int checkMatch(char, char);
int getMaxOrZero(int, int, int);
std::vector<std::vector<DP_Cell> > globalAlignment(std::string, std::string);
int tracebackGlobal (std::vector<std::vector<DP_Cell> >, std::string *, std::string *);
std::vector<std::vector<DP_Cell> > localAlignment(std::string, std::string);
int tracebackLocal (std::vector<std::vector<DP_Cell> >, std::string*, std::string*);
void printReport(std::string, bool);

#endif