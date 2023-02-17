#include "header.hpp"

void readInputFile(std::string filename)
{
    extern std::string s1, s1Name, s2, s2Name;
    std::ifstream infile;
    std::string line;
    infile.open(filename);
    if (infile.is_open()){
        // read name for s1
        getline(infile, line);
        s1Name = line;

        // read sequence for s1
        getline(infile, line);
        while (line != ""){
            s1 += line;
            getline(infile, line);
        }

        // read name for s2
        getline(infile, line);
        s2Name = line;

        // read sequence for s2
        getline(infile, line);
        while(!infile.eof()){
            s2 += line;
            getline(infile, line);
        }
        getline(infile, line);
        s2+= line;

        infile.close();
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
    } 
}

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
    std::cout << "NeedlemanWunsch";
}