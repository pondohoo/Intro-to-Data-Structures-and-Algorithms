#include <iostream>
#include <fstream>

using namespace std;

#include "Compression.h"

int main(int argc, char* argv[])
{
    
    // file names entered are not in right format 
    if (argc != 2)
    {
        cout << "Enter: progFile dataFile" << endl;
        return -1;
    }
    Compression compressingFile(argv[1]);

    // reading data from file
    compressingFile.HashItUp();

    compressingFile.UnhashItUp();


    return 0;

}