#include "args.h"

#include <iostream>
#include <string>
#include <stdexcept>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

void Args::read(int argc, char** argv) 
{
    for (int index = 1; index < argc; index++)
    {
        if (strcmp(argv[index], "-c") == 0 || strcmp(argv[index], "--config") == 0)
        {
            configPath = string(argv[index + 1]);
            index++;
            continue;
        }
        else if (strcmp(argv[index], "-f") == 0 || strcmp(argv[index], "--file") == 0)
        {
            xlsxPath = string(argv[index + 1]);
            index++;
            continue;
        }
        else if (strcmp(argv[index], "-o") == 0 || strcmp(argv[index], "--output") == 0)
        {
            outputPath = string(argv[index + 1]);
            index++;
            continue;
        }
    }
}

int Args::validate() 
{
    if (xlsxPath == "")
    {
        throw std::invalid_argument("No Xlsx File Specified");
    }
    if (configPath == "")
    {
        throw std::invalid_argument("No Config File Specified");
    }
    return 0;
}