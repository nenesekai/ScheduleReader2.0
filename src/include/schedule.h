#pragma once

#include <list>
#include <string>
#include <vector>

#include "OpenXLSX.hpp"
#include "args.h"
#include "calendar.h"
#include "date/date.h"
#include "date/tz.h"
#include "logger.h"
#include "nlohmann/json.hpp"

using nlohmann::json;

class Schedule {
public:
    struct Day {
        int day;
        std::string col, timeCol;
        Day(int d, std::string c, std::string tc)
            : day(d)
            , col(c)
            , timeCol(tc) {};
    };

    struct Lesson {
        int start, end;
        Lesson(int s, int e)
            : start(s)
            , end(e) {};
    };

    OpenXLSX::XLDocument doc;
    OpenXLSX::XLWorksheet wks;

    std::vector<std::string> exclude;
    std::vector<std::string> exclude_all;
    std::vector<std::string> coursesTaken;
    std::vector<Day> days;
    std::vector<Lesson> lessons;
    std::vector<Event> events;

    std::list<std::string> all_lessons;

    std::string time_sep = "-";
    std::string hm_sep = ":";
    std::string timezone = "Asia/Shanghai";
    std::string wksName;
    std::string allLessonsPath;
  
    date::local_days monday = date::local_days{date::April/30/2004};

    bool isExclude = false, isExcludeAll = false, isAllLessons = false, haveClasses = false;
    int location_length = 4;

    Logger* logger;

    Schedule(Logger* logger)
        : logger(logger) {};

    void parseEvents();

    void openDoc(std::string path);
    void readConfig(json& config);
    void openWks();
    void readArgs(Args args);
    void exportAllLessons(std::string path);
    bool validate(std::string& content);
    bool taken(std::string& content);
};
