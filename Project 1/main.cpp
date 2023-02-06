#include "header.hpp"

int main(int argc, char* argv[])
{
    std::ofstream outfile;
    outfile.open("Report.txt");
    outfile << "Hi";
    outfile.close(); 
    return 0;
}