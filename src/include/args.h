#pragma once

#include <string>

#include "logger.h"

class Args
{
public:
    std::string xlsxPath, configPath, outputPath, listPath, mondayOverride;
    logger* logger;

    Args(class logger* logger): logger(logger) {};

    void read(int argc, char **argv);
    int validate();
};