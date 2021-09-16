#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "date/tz.h"

class Event 
{
public:
    std::string summary, location, description;
    std::string format = "%Y%m%dT%H%M%SZ";
    std::string timezone = "Asia/Shanghai";
    std::string outputTimeZone = "UTC";
    date::zoned_time<std::chrono::seconds> timeStart, timeEnd;

    Event(std::string summary): summary(summary) {};
    Event(std::string content, int location_length);

    void write(std::ofstream& ofs);
    void parse_time(date::local_days date, std::string timeRaw, std::string time_sep = "-", std::string hm_sep = ":");
};

class Calendar
{
public:
    std::string calname = "Schedule";
    std::vector<Event> events;
    
    void to_ical(std::string path);
};