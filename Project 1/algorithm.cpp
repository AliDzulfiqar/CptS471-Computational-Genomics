#include "header.hpp"

// read input (FASTA) files from command line
// void readInput(std::string filename)
// {
//     extern std::string s1, s2, s1Name, s2Name;
//     std::ifstream infile;
//     std::string line;
//     infile.open(filename);

//     if (infile.is_open())
//     {
//         getline(infile, line);
//         s1Name = line;

//         getline(infile, line);
//         while(line.length() != 0)
//         {
//             s1+= line;
//             getline(infile, line);
//         }

//         getline(infile, line);
//         s2Name = line;

//         getline(infile, line);
//         while(line.length() != 0)
//         {
//             s2+= line;
//             getline(infile, line);
//         }
//     }
//     else{
//         std::cout << "Cannot open file" << std::endl;
//     }

//     infile.close();
// }

// // read from config file from command line
// void readConfig(std::string filename)
// {
//     extern int match, mismatch, h, g;
//     std::string line;
//     std::ifstream infile;
//     // infile.open(filename);
// }

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

int calcCost(char a, char b){
    extern int match, mismatch;
    if (a == b){
        return match;
    }
    return mismatch;
}

std::vector<std::vector<DP_Cell> > NeedlemanWunsch(std::string s1, std::string s2){
    int m = s1.length();
    int n = s2.length();

    extern int h, g;

    //Initialize scoring Matrix
    std::vector<std::vector<DP_Cell> > DP_Table (m+1, std::vector<DP_Cell>(n+1));
    for (int i = 0; i <= m; i++){
        DP_Table[i][0].dScore = h + i * g;
    }
    for (int j = 0; j <= n; j++){
        DP_Table[0][j].iScore = h + j * g;
    }

    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            int cost = calcCost(s1[i-1], s2[j-1]);
            int option1 = DP_Table[i - 1][j - 1].sScore + cost;
            int option2 = DP_Table[i- 1][j].dScore + g;
            int option3 = DP_Table[i][j - 1].iScore + g;
            DP_Table[i][j].sScore = getMaxOf3Int(option1, option2, option3);
            DP_Table[i][j].dScore = std::max(DP_Table[i-1][j].dScore + g, DP_Table[i][j].sScore + g + h);
            DP_Table[i][j].iScore = std::max(DP_Table[i][j-1].iScore + g, DP_Table[i][j].sScore + g + h);
        }
    }

    return DP_Table;

}

