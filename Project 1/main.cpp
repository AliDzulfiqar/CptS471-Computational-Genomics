#include "header.hpp"

// Define globals
std::string s1, s2, s1Name, s2Name;
int match = 1, mismatch = -2, h = -5, g = -1;
int totalMatches, totalMismatches, openingGaps, gapExtensions;

int main(int argc, char* argv[])
{   
    std::string tracebackS1, tracebackS2;
    int score = 0, s1GapCount = 0, s2GapCount = 0;
    bool alignmentType = false; // 0 for global, 1 for local
    if (argc >= 4){
        readInputFile(argv[1]);
        alignmentType = std::stoi(argv[2]);
        readConfigFile(argv[3]);
    }

    // Printing report.txt
    std::ofstream outfile;
    outfile.open("Report.txt");
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
        outfile << "Global Substitution Score: " << globalTable[s1.length()][s2.length()].sScore << std::endl;
        outfile << "Global Deletion Score: " << globalTable[s1.length()][s2.length()].dScore << std::endl;
        outfile << "Global Insertion Score: " << globalTable[s1.length()][s2.length()].iScore << std::endl;
        outfile << "Global Value: " << globalTable[s1.length()][s2.length()].value << std::endl;
        std::cout << "Traceback global: " << tracebackGlobal(globalTable, &tracebackS1, &tracebackS2) << std::endl;
        // std::cout << "Traceback s1" << tracebackS1 << std::endl;
        // std::cout << "Traceback s2" << tracebackS2 << std::endl;
    }
   

    outfile.close();
    
}