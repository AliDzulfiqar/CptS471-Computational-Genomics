#include "header.hpp"

// Define globals
std::unordered_map<char, int> alphabetValues;
std::string s1, s1Name;


int main(int argc, char* argv[])
{   
    /* $ 
    Using command line to input string. 
    Run $ <test executable> <input file containing sequence s> <input alphabet file> on terminal
    */

    if(argc > 2){
        readInputFile(argv[1]);
        readAlphabetFile(argv[2]);
    }
    else {
        std::cout << "Missing input file. Expected one input file containing sequence and one input containing alphabet file." << std::endl;
    }

    // Report
    std::cout << "Number of Internal Nodes" << std::endl;
    std::cout << "Leaves" << std::endl;
    std::cout << "Total Number of Nodes" << std::endl;
    std::cout << "Average string depth of the deepest internal node" << std::endl;
    std::cout << "String depth of the deepest internal Nodes" << std::endl;


    // // // Use C++11
    // for (auto it = alphabetValues.begin(); it != alphabetValues.end(); it++) {
    //     std::cout << it->first << ": " << it->second << std::endl;
    // }

    return 0;
    
}