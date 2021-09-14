#pragma once
#include "nlohmann/json.hpp"
#include <string>
#include <vector>
#include <list>

#include "OpenXLSX.hpp"
#include "calendar.h"
#include "date/tz.h"
#include "date/date.h"

using nlohmann::json;

class Schedule
{
public:
    struct Day
    {
        int day;
        std::string col, timeCol;
        Day(int d, std::string c, std::string tc): day(d), col(c), timeCol(tc) {};
    };

    struct Lesson
    {
        int start, end;
        Lesson(int s, int e): start(s), end(e) {};
    };

    OpenXLSX::XLDocument doc;
    OpenXLSX::XLWorksheet wks;
    
    std::vector<std::string> exclude;
    std::vector<std::string> exclude_all;
    std::vector<std::string> classes;
    std::vector<Day> days;
    std::vector<Lesson> lessons;
    date::year_month_day monday = date::April/30/2004;

    std::list<std::string> all_lessons;
    std::string time_sep = "-";
    std::string hs_sep = ":";

    bool isExclude = false, isExcludeAll = false;
    int location_length = 4;

    std::vector<Event> parseEvents();

    void readFromFile(std::string path, std::string wksName);
    void readConfig(json& config);
    void exportAllLessons(std::string path);
    bool validate(std::string& content);
    bool taken(std::string& content);
};