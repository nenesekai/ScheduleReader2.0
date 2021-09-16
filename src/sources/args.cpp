#include "args.h"

#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>

void Args::read(int argc, char** argv) 
{
    logger->info("-- Reading Arguments --");
    for (int index = 1; index < argc; index++)
    {
        logger->info("Argument Found: " + std::string(argv[index]));

        if (strcmp(argv[index], "-c") == 0 || strcmp(argv[index], "--config") == 0)
        {
            configPath = std::string(argv[index + 1]);
            index++;
            continue;
        }
        else if (strcmp(argv[index], "-f") == 0 || strcmp(argv[index], "--file") == 0)
        {
            xlsxPath = std::string(argv[index + 1]);
            index++;
            continue;
        }
        else if (strcmp(argv[index], "-o") == 0 || strcmp(argv[index], "--output") == 0)
        {
            if (index == argc - 1 || argv[index + 1][0] == '-')
            {
                outputPath = "./output.ics";
                continue;
            }
            else
            {
                outputPath = std::string(argv[index + 1]);
                index++;
                continue;
            }
        }
        else if (strcmp(argv[index], "-l") == 0 || strcmp(argv[index], "--list") == 0)
        {
            listPath = std::string(argv[index + 1]);
            index++;
            continue;
        }
        else if (strcmp(argv[index], "-m") == 0 || strcmp(argv[index], "--monday") == 0)
        {
            mondayOverride = std::string(argv[index + 1]);
            index++;
            continue;
        }
        else if (strcmp(argv[index], "--log") == 0)
        {
            logger->level = std::stoi(argv[index + 1]);
            index++;
            continue;
        }
        else if (strcmp(argv[index], "-h") == 0 || strcmp(argv[index], "--help") == 0)
        {
            std::cout << "Usage: \n"
                << "  schedule --file /path/to/schedule.xlsx --config /path/to/config.json [options]\n"
                << "\n"
                << "Options:\n"
                << "-l or --list /path/to/list.txt\n"
                << "  Create a list in the directory specified that contains all lessons scanned\n\n"
                << "-o or --output [path/to/icalendar.ics]\n"
                << "  Create a icalendar file in the directory that contains all lessons taken by you noted in config\n"
                << "  If directory not specified, it will be ./output.ics\n"
                << "  Note: If classes is not specified in config, it will add all classes detected\n\n" 
                << "--log 0/1/2\n"
                << "  set log level, 0: error only, 1: error and warning, 2: everything\n\n"
                << "-m or --monday yyyy-mm-dd\n"
                << "  Override the Monday Date in config file\n" << std::endl;
            
            exit(0);
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
