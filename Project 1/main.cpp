#include "header.hpp"

// Define globals
std::string s1, s2, s1Name, s2Name;
int match = 1, mismatch = -2, h = -5, g = -2, totalMatches, totalMismatches, openingGaps, gapExtensions;

int main(int argc, char* argv[])
{
    int score = 0, s1GapCount = 0, s2GapCount = 0;
    bool alignmentType = 0;
    if (argc >= 4){
        readInputFile(argv[1]);
        alignmentType = std::stoi(argv[2]);
        readConfigFile(argv[3]);
    }
    // readConfigFile("parameters.config");
    
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


    outfile.close();
    
}