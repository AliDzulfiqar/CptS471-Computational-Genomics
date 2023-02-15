#include "header.hpp"

int getMaxOf3Int(int i, int s, int d)
{
    return std::max(i, std::max(s, d));
}


int getMaxOrZero(int i, int s, int d){
    if (i < 0 && s < 0 && d < 0){
        return 0;
    }
    return getMaxOf3Int(i, s, d);
}

int checkMatch(char a, char b){
    extern int match, mismatch;
    if (a == b){
        return match;
    }
    return mismatch;
}

void needlemanWunsch(){
    std::cout << "NeedlemanWunsch"
}