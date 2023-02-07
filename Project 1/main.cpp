#include "header.hpp"

int main(int argc, char* argv[])
{
    std::ofstream outfile;
    outfile.open("Report.txt");
    outfile << "Hi";
    outfile.close();
    
    int a = 1, b = 2, c = 3;
    int max = getMaxOf3Int(a, b, c);
    std::cout << max;
    return 0;
}