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
    extern std::unordered_map<char, int> alphabetValues;
    std::ifstream infile;
    std::string line;
    
    infile.open(filename);
    if(infile.is_open()) {
        alphabetValues['$'] = 0;
        getline(infile, line);

        for (int i = 0; i < line.length(); i++) {
            char c = line[i];
            alphabetValues[c] = alphabetValues.size();
        }
    }
    else {
        std::cout << "Cannot open file" << std::endl;
    }
}

// // Finds the path starting at the specified node argument that spells out the longest possible prefix of the specified string argument, then insert the next suffix
// STNode* SuffixTree::findPath(STNode *u, std::string s, int i){

//     // Initialize
//     // v-> u, x -> s
//     // Repeat:
//     // IF no existing branch{
//     //     insert new leaf for s under u
//     //     return
//     // }

//     // Compare characters of the edge label against x until first mismatch or edgelable exhausted

//     // if mismatch {
//     //     break edge 
//     //     create new internal node 
//     //     create new leaf for s under that node 
//     //     return 
//     // }
//     // else {
//     //     v-> next internal node 
//     //     x-> x 
//     // }

//     // until (leaf inserted)
//     extern std::unordered_map<char, int> alphabetValues;
//     STNode *v = u;
//     std::string x = s;
//     while(true) {
//         // case of no existing branch
//         if (u->children == nullptr) {
//             u->children[alphabetValues[x[0]]] = new STNode(i, u, u->children->start, u->children->end);
//             return u->children[alphabetValues[x[0]]];
//         }
//     }
// }


// // Build naive tree
// STNode* SuffixTree::buildNaiveTree(std::string str) {
//     // T = null
//     // for i to n{
//     // Ti insert. Find path(root, s..i)
//     // }
//     // return tree

//     root = nullptr;
//     STNode *t = root;
//     for (int i = 0; i < str.length(); i++){
//         findPath(root, str, i);
//     }
//     return t;
// }

