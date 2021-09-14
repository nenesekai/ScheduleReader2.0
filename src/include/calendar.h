#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "time.h"
#include "date/date.h"

class Time
{
public:
    int hour, minute, second;

    Time(): hour(0), minute(0), second(0) {};
    Time(int hour, int minute, int second): hour(hour), minute(minute), second(second) {};
    Time(std::string content, std::string hs_sep);

    static std::string twodigit(int num);

    std::string to_string();
    void from_string(std::string content, std::string hs_sep);
};

class Time_Interval
{
public:
    Time start = Time(), end = Time();

    Time_Interval(std::string content, std::string time_sep, std::string hm_sep);
};

class Event 
{
public:
    std::string summary, location, dtstart, dtend, description;

    Event(std::string summary): summary(summary) {};
    Event(std::string content, int location_length);

    void write(std::ofstream& ofs);
};

class Calendar
{
public:
    std::string calname = "Schedule";
    std::string timezone = "Asia/Shanghai";
    std::vector<Event> events;

    static std::string todt(date::year_month_day date, Time time);
    
    void to_ical(std::string path);
};