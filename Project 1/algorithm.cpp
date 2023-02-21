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

void readConfigFile(std::string filename)
{
    extern int match, mismatch, h, g;
    int matchTemp, mismatchTemp, hTemp, gTemp;
    std::ifstream infile;
    std::string line, delimeter = " ", token;
    infile.open(filename);

    if(infile.is_open()){
        for (int i = 0; i < 4; i++){
            getline(infile, line);
            token = line.substr(line.find(delimeter) + 1);
            if(i == 0){
                match = std::stoi(token);
            }
            if (i == 1) {
                mismatch = std::stoi(token);
            } 
            if (i == 2) {
                h= std::stoi(token);

            } 
            if (i == 3) {
                g = std::stoi(token);
            }
        }
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

std::vector<std::vector<DP_Cell> > globalAlignment(std::string s1, std::string s2)
{
    int m = s1.length();
    int n = s2.length();

    extern int h, g;

    // initialize matrix
    std::vector<std::vector<DP_Cell> > DPTable(m + 1, std::vector<DP_Cell>(n + 1));
    for (int i = 0; i <= m; i++){
        DPTable[i][0].sScore = INT_MIN - h - g;
        DPTable[i][0].dScore = h + i * g;
        DPTable[i][0].iScore = INT_MIN - h - g;
    }
    for (int j = 0; j <= n; j++){
        DPTable[0][j].sScore = INT_MIN - h - g;
        DPTable[0][j].dScore = INT_MIN - h - g;
        DPTable[0][j].iScore = h + j * g;
    }

    // iterate each elements of the matrix
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            // find max score
            DPTable[i][j].sScore = getMaxOf3Int(DPTable[i - 1][j - 1].sScore,DPTable[i - 1][j - 1].dScore,DPTable[i - 1][j - 1].iScore) + checkMatch(s1[i - 1], s2[j - 1]);
            DPTable[i][j].dScore = getMaxOf3Int(DPTable[i - 1][j].sScore + g + h, DPTable[i - 1][j].dScore + g, DPTable[i - 1][j].iScore + g + h);
            DPTable[i][j].iScore = getMaxOf3Int(DPTable[i][j - 1].sScore + g + h, DPTable[i][j - 1].dScore + g + h, DPTable[i][j - 1].iScore + g);
        }
    }

    return DPTable;
}

std::vector<std::vector<DP_Cell> > localAlignment(std::string s1, std::string s2)
{
    int m = s1.length();
    int n = s2.length();

    extern int h, g;

    // initialize matrix
    std::vector<std::vector<DP_Cell> > DPTable(m + 1, std::vector<DP_Cell>(n + 1));
    for (int i = 0; i <= m; i++){
        DPTable[i][0].dScore = h + i * g;
    }
    for (int j = 0; j <= n; j++){
        DPTable[0][j].iScore = h + j * g;
    }

    for (int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            int path1 = DPTable[i - 1][j - 1].sScore + checkMatch(s1[i - 1], s2[j - 1]);
            int path2 = DPTable[i - 1][j].dScore + g;
            int path3 = DPTable[i][j - 1].iScore + g;
            // get max score
            DPTable[i][j].sScore = getMaxOrZero(path1, path2, path3);
            DPTable[i][j].dScore = std::max(path2, DPTable[i][j].sScore + g + h);
            DPTable[i][j].iScore = std::max(path3, DPTable[i][j].sScore + g + h);
        }
    }

    return DPTable;
}