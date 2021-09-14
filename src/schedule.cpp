#include "schedule.h"
#include "nlohmann/json.hpp"
#include "OpenXLSX.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "date/date.h"
#include "date/tz.h"

using nlohmann::json;

bool Schedule::validate(std::string &content)
{
    if (isExclude)
    {
        for (std::vector<std::string>::iterator excludeIter = exclude.begin(); excludeIter < exclude.end(); excludeIter++)
        {
            if (content.find(*excludeIter) != std::string::npos)
            {
                return false;
            }
        }
    }
    if (isExcludeAll)
    {
        for (std::vector<std::string>::iterator excludeAllIter = exclude_all.begin(); excludeAllIter < exclude_all.end(); excludeAllIter++)
        {
            if (content.compare(*excludeAllIter) == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool Schedule::taken(std::string &content)
{
    for (std::vector<std::string>::iterator iter = classes.begin(); iter < classes.end(); iter++)
    {
        if (content.find(*iter) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}

std::vector<Event> Schedule::parseEvents()
{
    std::vector<Event> events;

    for (std::vector<Day>::iterator dayIter = days.begin(); dayIter < days.end(); dayIter++)
    {
        for (std::vector<Lesson>::iterator lessonIter = lessons.begin(); lessonIter < lessons.end(); lessonIter++)
        {
            for (int index = lessonIter->start; index <= lessonIter->end; index++)
            {
                std::string content = wks.cell(dayIter->col + std::to_string(index)).value().get<std::string>();
                std::string timeRaw = wks.cell(dayIter->timeCol + std::to_string(lessonIter->start)).value().get<std::string>();
                if (validate(content))
                {
                    all_lessons.push_back(content);
                    all_lessons.unique();
                    if (taken(content))
                    {
                        Event event(content, location_length);

                        Time_Interval ti(timeRaw, time_sep, hs_sep);
                        auto date = date::year_month_day{date::sys_days{monday} + date::days{dayIter->day} - date::days{1}};
                        event.dtstart = Calendar::todt(date, ti.start);
                        event.dtend = Calendar::todt(date, ti.end);

                        events.push_back(event);
                    }
                }
            }
        }
    }

    return events;
}


void Schedule::readFromFile(std::string path, std::string wksName = "null")
{
    doc.open(path);

    if (wksName == "null")
    {
        wksName = doc.workbook().worksheetNames()[0];
    }
    wks = doc.workbook().worksheet(wksName);
}

void Schedule::readConfig(json& config)
{
    if (config["exclude"] != "null")
    {
        isExclude = true;

        for (std::string dir: config["exclude"])
        {
            exclude.push_back(dir);
        }
        exclude = config["exclude"].get<std::vector<std::string>>();
    }
    if (config["exclude_all"] != "null")
    {
        isExcludeAll = true;
        exclude_all = config["exclude_all"].get<std::vector<std::string>>();
    }
    classes = config["classes"].get<std::vector<std::string>>();

    for (auto day: config["days"])
    {
        Day d(day["day"], day["col"], day["time"]);
        days.push_back(d);
    }

    for (auto lesson: config["lessons"])
    {
        Lesson l(lesson["start"], lesson["end"]);
        lessons.push_back(l);
    }

    std::istringstream is{config["monday"].get<std::string>()};
    date::sys_days sd;
    is >> date::parse("%F", sd);
    monday = sd;

    location_length = config["location_length"] == "null" ? location_length : config["location_length"].get<int>();
    time_sep = config["time_sep"] == "null" ? time_sep : config["time_sep"].get<std::string>();
    hs_sep = config["hs_sep"] == "null" ? hs_sep : config["hs_sep"].get<std::string>();
}

void Schedule::exportAllLessons(std::string path)
{
    std::ofstream ofs(path);
    for (std::string str: all_lessons)
    {
        ofs << str << std::endl;
    }
    ofs.close();
}
