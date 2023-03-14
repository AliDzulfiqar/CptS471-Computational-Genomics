#include "header.hpp"

// Read input file (.fasta)
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

// Read configuration file for scoring parameters
void readConfigFile(std::string filename)
{
    extern int match, mismatch, h, g;
    int matchTemp, mismatchTemp, hTemp, gTemp;
    std::ifstream infile;
    std::string line, delimeter = " ", token;
    infile.open(filename);
    if(infile.is_open()){
        // loop 4 times for 4 lines
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

// Get a maximum value of 3 integers
int getMaxOf3Int(int i, int s, int d)
{
    return std::max(i, std::max(s, d));
}

// Get a maximum value of integer. However if all values are negative, return 0
int getMaxOrZero(int i, int s, int d){
    if (i < 0 && s < 0 && d < 0){
        return 0;
    }
    else {
        return getMaxOf3Int(i, s, d);
    }
    
}

// Determine whether string is a match or a mismatch
int checkMatch(char a, char b){
    extern int match, mismatch;
    if (a == b){
        return match;
    }
    return mismatch;
}

// Create a 2x2 table for Global Alignment
std::vector<std::vector<DP_Cell> > globalAlignment(std::string s1, std::string s2)
{
    // determine size m and n for vector
    int m = s1.length() + 1;
    int n = s2.length() + 1;

    extern int h, g;

    // initialize matrix
    std::vector<std::vector<DP_Cell> > DPTable(m + 1, std::vector<DP_Cell>(n + 1));
    for (int i = 0; i < m; i++){
        DPTable[i][0].value = i * g;
        DPTable[i][0].cases = deletion;
        DPTable[i][0].sScore = INT_MIN - h - g;
        DPTable[i][0].dScore = h + i * g;
        DPTable[i][0].iScore = INT_MIN - h - g;
    }
    for (int j = 0; j < n; j++){
        DPTable[0][j].value = j * g;
        DPTable[0][j].cases = insertion;
        DPTable[0][j].sScore = INT_MIN - h - g;
        DPTable[0][j].dScore = INT_MIN - h - g;
        DPTable[0][j].iScore = h + j * g;
    }

    // iterate each elements of the matrix
    for (int i = 1; i < m; i++){
        for (int j = 1; j < n; j++){
            // find max score
            DPTable[i][j].sScore = getMaxOf3Int(DPTable[i - 1][j - 1].sScore,DPTable[i - 1][j - 1].dScore,DPTable[i - 1][j - 1].iScore) + checkMatch(s1[i - 1], s2[j - 1]);
            DPTable[i][j].dScore = getMaxOf3Int(DPTable[i - 1][j].sScore + g + h, DPTable[i - 1][j].dScore + g, DPTable[i - 1][j].iScore + g + h);
            DPTable[i][j].iScore = getMaxOf3Int(DPTable[i][j - 1].sScore + g + h, DPTable[i][j - 1].dScore + g + h, DPTable[i][j - 1].iScore + g);

            // find cases to proceed
            if(DPTable[i][j].sScore > std::max(DPTable[i][j].dScore, DPTable[i][j].iScore)){
                DPTable[i][j].cases = substitution;
                DPTable[i][j].value = DPTable[i][j].sScore;
            }
            else if (DPTable[i][j].dScore > DPTable[i][j].iScore){
                DPTable[i][j].cases = deletion;
                DPTable[i][j].value = DPTable[i][j].dScore;
            }
            else {
                DPTable[i][j].cases = insertion;
                DPTable[i][j].value = DPTable[i][j].iScore;
            }
        }

    }

    return DPTable;
}

// Traceback algorithm for global alignment
int tracebackGlobal (std::vector<std::vector<DP_Cell> > globalTable, std::string *tracebackS1, std::string *tracebackS2)
{
    extern std::string s1, s2;
    int i = s1.length(), j = s2.length();
    int score = globalTable[i][j].value;
    
    DP_Cell current = globalTable[i][j];
    
    // Retrace the table based on each cases. Produce 2 aligned string values
    while(i >= 0 && j >= 0){
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
        switch (current.cases)
        {
        case insertion:
            j--;
            *tracebackS1 += '-';
            if (j >= 0){
                *tracebackS2 += s2[j];
            }
            else {
                *tracebackS2 += '-';
            }
            break;
        
        case substitution:
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

        case deletion:
            i--;
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

// Create a 2x2 table for Local Alignment
std::vector<std::vector<DP_Cell> > localAlignment(std::string s1, std::string s2)
{
    int m = s1.length() + 1;
    int n = s2.length() + 1;

    extern int h, g;

    // initialize matrix
    std::vector<std::vector<DP_Cell> > DPTable(m + 1, std::vector<DP_Cell>(n + 1));
    for (int i = 0; i < m; i++){
        DPTable[i][0].value = 0;
        DPTable[i][0].cases = deletion;
        DPTable[i][0].sScore = INT_MIN - h - g;
        DPTable[i][0].dScore = h + i * g;
        DPTable[i][0].iScore = INT_MIN - h - g;
    }
    for (int j = 0; j < n; j++){
        DPTable[0][j].value = 0;
        DPTable[0][j].cases = insertion;
        DPTable[0][j].sScore = INT_MIN - h - g;
        DPTable[0][j].dScore = INT_MIN - h - g;
        DPTable[0][j].iScore = h + j * g;
    }

    // iterate each elements of the matrix
    for (int i = 1; i < m; i++){
        for (int j = 1; j < n; j++){

            // find max score
            DPTable[i][j].sScore = getMaxOrZero(DPTable[i - 1][j - 1].sScore,DPTable[i - 1][j - 1].dScore,DPTable[i - 1][j - 1].iScore) + checkMatch(s1[i - 1], s2[j - 1]);
            DPTable[i][j].dScore = getMaxOrZero(DPTable[i - 1][j].sScore + g + h, DPTable[i - 1][j].dScore + g, DPTable[i - 1][j].iScore + g + h);
            DPTable[i][j].iScore = getMaxOrZero(DPTable[i][j - 1].sScore + g + h, DPTable[i][j - 1].dScore + g + h, DPTable[i][j - 1].iScore + g);

            // find cases to proceed
            if(DPTable[i][j].sScore > std::max(DPTable[i][j].dScore, DPTable[i][j].iScore)){
                DPTable[i][j].cases = substitution;
                DPTable[i][j].value = DPTable[i][j].sScore;
            }
            else if (DPTable[i][j].dScore > DPTable[i][j].iScore){
                DPTable[i][j].cases = deletion;
                DPTable[i][j].value = DPTable[i][j].dScore;
            }
            else {
                DPTable[i][j].cases = insertion;
                DPTable[i][j].value = DPTable[i][j].iScore;
            }
        }
    }

    return DPTable;
}

// Traceback algorithm for Local Alignment
int tracebackLocal (std::vector<std::vector<DP_Cell> > localTable, std::string* tracebackS1, std::string* tracebackS2)
{  
    extern std::string s1, s2;
    int maxI, maxJ;
    int score = 0;

    // finding max indexes
    for (int i = 0; i < localTable.size(); i++){
        for (int j = 0; j < localTable[0].size(); j++){
            if(localTable[i][j].value > score){
                score = localTable[i][j].value;
                maxI = i;
                maxJ = j;
            }
        }
    }

    DP_Cell current = localTable[maxI][maxJ];

    // Retrace the algorithm to find optimal score and produce two aligned string
    while(current.value > 0){
        switch (current.cases)
        {
        case insertion:
            maxJ--;
            *tracebackS1 += '-';
            if (maxJ >= 0){
                *tracebackS2 += s2[maxJ];
            }
            else {
                *tracebackS2 += '-';
            }
            break;
        
        case substitution:
            maxI--;
            maxJ--;
            if (maxI >= 0){
                *tracebackS1 += s1[maxI];
            }
            else {
                *tracebackS1 += '-';
            }
            if (maxJ >= 0){
                *tracebackS2 += s2[maxJ];
            }
            else {
                *tracebackS2 += '-';
            }
            break;

        case deletion:
            maxI--;
            if (maxI >= 0){
                *tracebackS1 += s1[maxI];
            }
            else {
                *tracebackS1 += '-';
            }
            *tracebackS2 += '-';
            break;
        }

        current = localTable[maxI][maxJ];
    }
    return score;
}

// Print report
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
    
    // determine outfile based on alignment type
    if(alignmentType){
        std::vector<std::vector <DP_Cell> > localTable = localAlignment(s1, s2);
        optimalScore = tracebackLocal(localTable, &tracebackS1, &tracebackS2);
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
        outfile << std::endl;
        outfile << "Report:" << std::endl;
        outfile << std::endl;
        outfile << "Local Optimal Score: " << optimalScore << std::endl;
        outfile << std::endl;
        outfile << "Number of:  matches = " << totalMatches << ", mismatches = " << totalMismatches << ", opening gaps = " << openingGaps << ", gap extensions = " << gapExtensions<< std::endl;
        outfile << "Identities = " << totalMatches << "/" << tracebackS1.length() << " (" << ((floor)((double)totalMatches/(double)tracebackS1.length()*100)) << "%), " << "Gaps = " << gapExtensions << "/" << tracebackS1.length() << " (" << ((floor)((double)gapExtensions/(double)tracebackS1.length()*100)) << "%)";

    }
    else {
        std::vector<std::vector <DP_Cell> > globalTable = globalAlignment(s1, s2);
        optimalScore = tracebackGlobal(globalTable, &tracebackS1, &tracebackS2);
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
        outfile << std::endl;
        outfile << "Report:" << std::endl;
        outfile << std::endl;
        outfile << "Global Optimal Score: " << optimalScore << std::endl;
        outfile << std::endl;
        outfile << "Number of:  matches = " << totalMatches << ", mismatches = " << totalMismatches << ", opening gaps = " << openingGaps << ", gap extensions = " << gapExtensions<< std::endl;
        outfile << "Identities = " << totalMatches << "/" << tracebackS1.length() << " (" << ((floor)((double)totalMatches/(double)tracebackS1.length()*100)) << "%), " << "Gaps = " << gapExtensions << "/" << tracebackS1.length() << " (" << ((floor)((double)gapExtensions/(double)tracebackS1.length()*100)) << "%)";

    }

    outfile.close();
}
