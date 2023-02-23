#include "header.hpp"

// Define globals
std::string s1, s2, s1Name, s2Name;
int match = 1, mismatch = -2, h = -5, g = -1;
int totalMatches, totalMismatches, openingGaps, gapExtensions;

int main(int argc, char* argv[])
{   
    
    bool alignmentType = false; // 0 for global, 1 for local
    if (argc >= 4){
        readInputFile(argv[1]);
        alignmentType = std::stoi(argv[2]);
        readConfigFile(argv[3]);
    }

    // Printing report.txt
    printReport("Report.txt", alignmentType);
    
}