#pragma once

#include <iostream>
#include <string>

class Logger
{
public:
    int level;

    Logger(): level(0) {};
    Logger(int level): level(level) {};

    void err(std::string msg);
    void warning(std::string msg);
    void info(std::string msg);
    void report();
};
