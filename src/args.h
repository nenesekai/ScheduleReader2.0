#pragma once
#include <string>

class Args
{
public:
    std::string xlsxPath, configPath, outputPath = "./output.ics";
    void read(int argc, char **argv);
    int validate();
};