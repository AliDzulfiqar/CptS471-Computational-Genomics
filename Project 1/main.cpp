#include "header.hpp"

// Define globals
std::vector<std::vector<DP_Cell> > DP_Table;
std::string s1, s2, s1Name, s2Name;
int match = 1, mismatch = -1, h = 0, g = -2;
int totalMatch, totalMismatch, gapOpen, gapExtend;

int main(int argc, char* argv[])
{
    std::ifstream infile;
    std::string line;
    infile.open("Input.fasta");
    if (infile.is_open()){
        getline(infile, line);
        s1Name = line;
        std::cout << s1Name << std::endl;

        getline(infile, line);
        while (line != ""){
            s1 += line;
            getline(infile, line);
        }
        std::cout << s1 << std::endl;

        getline(infile, line);
        s2Name = line;
        std::cout << s2Name << std::endl;

        getline(infile, line);
        while(!infile.eof()){
            s2 += line;
            getline(infile, line);
        }
        std::cout << s2 << std::endl;
        infile.close();
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
    }

    

    // std::ofstream outfile;
    // outfile.open("Report.txt");
    // outfile << "Hi";
    // outfile.close();
    
}