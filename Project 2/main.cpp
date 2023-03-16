#include "header.hpp"

// Define globals
std::string s1, s1Name;


int main(int argc, char* argv[])
{   
    /* $ 
    Using command line to input string. 
    run $ <test executable> <input file containing sequence s> <input alphabet file> on terminal
    */

    if(argc > 2){
        readInputFile(argv[1]);
        readAlphabetFile(argv[2]);
    }
    else {
        std::cout << "Missing input file. Expected one input file containing sequence and one input containing alphabet file.";
    }
    
    



    return 0;
    
}