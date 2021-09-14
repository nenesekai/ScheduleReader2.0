#pragma once

#include <iostream>
#include <string>

class logger
{
public:
    int level;

    logger(): level(0) {};
    logger(int level): level(level) {};

    void err(std::string msg);
    void warning(std::string msg);
    void info(std::string msg);
    void report();
};