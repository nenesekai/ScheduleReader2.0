#include "logger.h"

#include <iostream>

void logger::info(std::string msg)
{
    if (level >= 2) std::cout << "[INFO] " << msg << std::endl;
}

void logger::warning(std::string msg) 
{
    if (level >= 1) std::cout << "[WARNING] " << msg << std::endl;
}

void logger::err(std::string msg)
{
    std::cerr << "[ERROR] " << msg << std::endl;
}

void logger::report()
{
    std::cout << "Current Log Level: " << level << std::endl;
}