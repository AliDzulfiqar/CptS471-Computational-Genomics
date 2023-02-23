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
    else {
        return getMaxOf3Int(i, s, d);
    }
    
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
        DPTable[i][0].value = i * g;
        DPTable[i][0].direction = up;
        DPTable[i][0].sScore = INT_MIN - h - g;
        DPTable[i][0].dScore = h + i * g;
        DPTable[i][0].iScore = INT_MIN - h - g;
    }
    for (int j = 0; j <= n; j++){
        DPTable[0][j].value = j * g;
        DPTable[0][j].direction = left;
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


            // find direction to proceed
            if(DPTable[i][j].sScore > std::max(DPTable[i][j].dScore, DPTable[i][j].iScore)){
                DPTable[i][j].direction = diagonal;
                DPTable[i][j].value = DPTable[i][j].sScore;
            }
            else if (DPTable[i][j].dScore > DPTable[i][j].iScore){
                DPTable[i][j].direction = up;
                DPTable[i][j].value = DPTable[i][j].dScore;
            }
            else {
                DPTable[i][j].direction = left;
                DPTable[i][j].value = DPTable[i][j].iScore;
            }
        }

    }

    return DPTable;
}

int tracebackGlobal (std::vector<std::vector<DP_Cell> > globalTable, std::string *tracebackS1, std::string *tracebackS2)
{
    extern std::string s1, s2;
    int i = s1.length(), j = s2.length();
    int score = globalTable[i][j].value;
    
    DP_Cell current = globalTable[i][j];
    
    while(i >= 0 && j >= 0 && tracebackS1){
        if (j < 0) {
            current = globalTable[i][0];
        }
        else if (i < 0) {
            current = globalTable[0][j];
        }
        else {
            current = globalTable[i][j];
        }
        if(i == 0 && j == 0){
            break;
        }
        switch (current.direction)
        {
        case left:
            --j;
            *tracebackS1 += '-';
            if (j >= 0){
                *tracebackS2 += s2[j];
            }
            else {
                *tracebackS2 += '-';
            }
            break;
        
        case diagonal:
            i--;
            j--;
            if (i >= 0){
                *tracebackS1 += s1[i];
            }
            else {
                *tracebackS1 += '-';
            }
            if (j >= 0){
                *tracebackS2 += s2[j];
            }
            else {
                *tracebackS2 += '-';
            }
            break;

        case up:
            --i;
            if (i >= 0){
                *tracebackS1 += s1[i];
            }
            else {
                *tracebackS1 += '-';
            }
            *tracebackS2 += '-';
            break;
        }
    }
    return score;
}

std::vector<std::vector<DP_Cell> > localAlignment(std::string s1, std::string s2)
{
    int m = s1.length();
    int n = s2.length();

    extern int h, g;

    // initialize matrix
    std::vector<std::vector<DP_Cell> > DPTable(m + 1, std::vector<DP_Cell>(n + 1));
    for (int i = 0; i <= m; i++){
        DPTable[i][0].value = 0;
        DPTable[i][0].direction = up;
        DPTable[i][0].sScore = INT_MIN - h - g;
        DPTable[i][0].dScore = h + i * g;
        DPTable[i][0].iScore = INT_MIN - h - g;
    }
    for (int j = 0; j <= n; j++){
        DPTable[0][j].value = 0;
        DPTable[0][j].direction = left;
        DPTable[0][j].sScore = INT_MIN - h - g;
        DPTable[0][j].dScore = INT_MIN - h - g;
        DPTable[0][j].iScore = h + j * g;
    }

    // iterate each elements of the matrix
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            // find max score
            DPTable[i][j].sScore = getMaxOrZero(DPTable[i - 1][j - 1].sScore,DPTable[i - 1][j - 1].dScore,DPTable[i - 1][j - 1].iScore) + checkMatch(s1[i - 1], s2[j - 1]);
            DPTable[i][j].dScore = getMaxOrZero(DPTable[i - 1][j].sScore + g + h, DPTable[i - 1][j].dScore + g, DPTable[i - 1][j].iScore + g + h);
            DPTable[i][j].iScore = getMaxOrZero(DPTable[i][j - 1].sScore + g + h, DPTable[i][j - 1].dScore + g + h, DPTable[i][j - 1].iScore + g);

            // find direction to proceed
            if(DPTable[i][j].sScore > std::max(DPTable[i][j].dScore, DPTable[i][j].iScore)){
                DPTable[i][j].direction = diagonal;
                DPTable[i][j].value = DPTable[i][j].sScore;
            }
            else if (DPTable[i][j].dScore > DPTable[i][j].iScore){
                DPTable[i][j].direction = up;
                DPTable[i][j].value = DPTable[i][j].dScore;
            }
            else {
                DPTable[i][j].direction = left;
                DPTable[i][j].value = DPTable[i][j].iScore;
            }
        }
    }

    return DPTable;
}

void printReport(std::string filename, bool alignmentType)
{
    // declare variables
    extern std::string s1, s2, s1Name, s2Name;
    extern int match, mismatch, h, g;
    extern int totalMatches, totalMismatches, openingGaps, gapExtensions;
    std::string tracebackS1, tracebackS2;
    int optimalScore = 0, s1GapCount = 0, s2GapCount = 0;

    // open file
    std::ofstream outfile;
    outfile.open(filename);

    // printing report
    outfile << "INPUT:\n******\n";
    outfile << std::endl;
    outfile << s1Name << "\n" << s1 << std::endl;
    outfile << std::endl;
    outfile << s2Name << "\n" << s2 << std::endl;
    outfile << std::endl;
    outfile << "OUTPUT:\n********\n";
    outfile << std::endl;
    outfile << "Scores:\t" << "match = " << match << ", mismatch = " << mismatch << ", h = " << h << ", g = " << g << std::endl;
    outfile << std::endl;
    outfile << "Sequence 1 = 's1', length = " << s1.length() << std::endl;
    outfile << "Sequence 2 = 's2', length = " << s2.length() << std::endl;
    outfile << std::endl;
    outfile << "Report:" << std::endl;

    if(alignmentType){
        std::vector<std::vector <DP_Cell> > localTable = localAlignment(s1, s2);
        outfile << "Local Substitution Score: " << localTable[s1.length()][s2.length()].sScore << std::endl;
        outfile << "Local Deletion Score: " << localTable[s1.length()][s2.length()].dScore << std::endl;
        outfile << "Local Insertion Score: " << localTable[s1.length()][s2.length()].iScore << std::endl;
        outfile << "Local Value: " << localTable[s1.length()][s2.length()].value << std::endl;
    }
    else {
        std::vector<std::vector <DP_Cell> > globalTable = globalAlignment(s1, s2);
        // outfile << "Global Substitution Score: " << globalTable[s1.length()][s2.length()].sScore << std::endl;
        // outfile << "Global Deletion Score: " << globalTable[s1.length()][s2.length()].dScore << std::endl;
        // outfile << "Global Insertion Score: " << globalTable[s1.length()][s2.length()].iScore << std::endl;
        // outfile << "Global Value: " << globalTable[s1.length()][s2.length()].value << std::endl;
        tracebackGlobal(globalTable, &tracebackS1, &tracebackS2);
        std::reverse(tracebackS1.begin(), tracebackS1.end());
        std::reverse(tracebackS2.begin(), tracebackS2.end());
        for (int i = 0; i < tracebackS1.length(); i++){
            outfile << tracebackS1[i];
        }
        outfile << std::endl;
        
        for (int i = 0; i < tracebackS1.length(); i++){
            
            if (tracebackS1[i] == tracebackS2[i]){
                outfile << "|";
                totalMatches++;
            }
            else if(tracebackS1[i] == '-'){
                outfile << " ";
                s1GapCount++;
                if (tracebackS1[i - 1] != '-')
                {
                    openingGaps++;
                    gapExtensions++;
                }
                else {
                    gapExtensions++;
                }
            }
            else if(tracebackS2[i] == '-'){
                outfile << " ";
                s2GapCount++;
                if (tracebackS2[i - 1] != '-')
                {
                    openingGaps++;
                    gapExtensions++;
                }
                else {
                    gapExtensions++;
                }
            }
            else {
                outfile << " ";
                totalMismatches++;
            }
        }
        outfile << std::endl;
        for (int i = 0; i < tracebackS2.length(); i++){
            outfile << tracebackS2[i];
        }

        outfile << std::endl;
        outfile << "Number of:  matches = " << totalMatches << ", mismatches = " << totalMismatches << ", opening gaps = " << openingGaps << ", gap extensions = " << gapExtensions<< std::endl;
        outfile << "Identities = " << totalMatches << "/" << tracebackS1.length() << " (" << ((floor)((double)totalMatches/(double)tracebackS1.length()*100)) << "%), " << "Gaps = " << gapExtensions << "/" << tracebackS1.length() << " (" << ((floor)((double)gapExtensions/(double)tracebackS1.length()*100)) << "%)";

    }

    outfile.close();
}
