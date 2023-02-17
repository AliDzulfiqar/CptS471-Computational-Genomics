#include "header.hpp"

// Define globals
std::string s1, s2, s1Name, s2Name;
int match = 1, mismatch = -2, h = -5, g = -2;

int main(int argc, char* argv[])
{
    readInputFile("Input.fasta");
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