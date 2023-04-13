#include "header.hpp"

// Define globals
std::unordered_map<char, int> alphabetValues;
std::string s1, s1Name;
int internalNodes = 0, numLeaves = 0, numNodes = 0, avgDepth = 0, deepestDepth = 0;

int main(int argc, char *argv[])
{
    /* $
    Using command line to input string.
    Run $ <test executable> <input file containing sequence s> <input alphabet file> on terminal
    */

    if (argc > 2)
    {
        std::string input = readInputFile(argv[1]);
        readAlphabetFile(argv[2]);
        SuffixTree stree;

        // Report
        auto start = std::chrono::high_resolution_clock::now();
        stree.buildNaiveTree(input);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Total runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
        std::cout << "Number of Internal Nodes" << internalNodes << std::endl;
        std::cout << "Leaves" << numLeaves << std::endl;
        std::cout << "Total Number of Nodes" << numNodes << std::endl;
        std::cout << "Average string depth of the deepest internal node" << avgDepth << std::endl;
        std::cout << "String depth of the deepest internal Nodes" << deepestDepth << std::endl;
    }
    else
    {
        std::cout << "Missing input file. Expected one input file containing sequence and one input containing alphabet file." << std::endl;
    }

    // // // Use C++11
    // for (auto it = alphabetValues.begin(); it != alphabetValues.end(); it++) {
    //     std::cout << it->first << ": " << it->second << std::endl;
    // }

    return 0;
}