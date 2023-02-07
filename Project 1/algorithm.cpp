#include "header.hpp"

// read input (FASTA) files from command line
void readInput(std::string filename)
{
    std::ifstream infile;
    std::string line, s1, s2, s1Name, s2Name;
    infile.open(filename);

    if (infile.is_open())
    {
        getline(infile, line);
        s1Name = line;

        getline(infile, line)
        while(line.length() != 0)
        {
            s1+= line;
            getline(infile, line);
        }

        getline(infile, line);
        s2Name = line;

        getline(infile, line)
        while(line.length() != 0)
        {
            s2+= line;
            getline(infile, line);
        }
    }
    else{
        std::cout << "Cannot open file" << std::endl;
    }

    infile.close();
}

// read from config file from command line
void readConfig(std::string filename)
{
    int match, mismatch, h, g;
    std::string line;
    std::ifstream infile;
    infile.open(filename);
}

int getMaxOf3Int(int i, int s, int d)
{
    return std::max(i, std::max(s, d));
}