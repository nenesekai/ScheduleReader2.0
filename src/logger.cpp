#include "logger.h"

#include <iostream>

void err(std::string msg)
{
    std::cerr << "[ERROR] " << msg << std::endl;
}

void warning(std::string msg) 
{
    std::cout << "[WARNING]" << msg << std::endl;
}

void info(std::string msg)
{
    std::cout << "[INFO]" << msg << std::endl;
}