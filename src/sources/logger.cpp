#include "logger.h"

#include <iostream>

void Logger::info(std::string msg)
{
    if (level >= 2) std::cout << "[INFO] " << msg << std::endl;
}

void Logger::warning(std::string msg) 
{
    if (level >= 1) std::cout << "[WARNING] " << msg << std::endl;
}

void Logger::err(std::string msg)
{
    std::cerr << "[ERROR] " << msg << std::endl;
}

void Logger::report()
{
    std::cout << "Current Log Level: " << level << std::endl;
}
