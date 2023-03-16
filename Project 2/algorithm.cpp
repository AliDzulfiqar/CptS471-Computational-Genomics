#include "header.hpp"

// Read input file (.fasta)
void readInputFile(std::string filename) {
    extern std::string s1, s1Name;
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

        infile.close();
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
    } 
}

void readAlphabetFile(std::string filename) {
    // extern std::unordered_map<char, int> alphabetValues;
    std::ifstream infile;
    std::string line;
    
    infile.open(filename);
    if(infile.is_open()) {
        // alphabetValues.insert(std::pair<char, int>("$", 0));
        getline(infile, line);

        // for (char c : line) {
        //     if (c != ' '){
        //         // alphabetValues.insert(std::pair<char, int>(c, alphabetValues.size()));
        //         std::cout << c;
        //     }
        // }
        // std::cout << line;
    }
    else {
        std::cout << "Cannot open file" << std::endl;
    }
}