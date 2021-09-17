#include "schedule.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "date/date.h"
#include "args.h"
#include "date/tz.h"
#include "nlohmann/json.hpp"
#include "OpenXLSX.hpp"
#include "logger.h"

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
    return content.length() >= location_length;
}

bool Schedule::taken(std::string &content)
{
    for (std::vector<std::string>::iterator iter = coursesTaken.begin(); iter < coursesTaken.end(); iter++)
    {
        if (content.find(*iter) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}

void Schedule::parseEvents()
{
    for (std::vector<Day>::iterator dayIter = days.begin(); dayIter < days.end(); dayIter++)
    {
        logger->info("Scanning Day " + std::to_string(dayIter->day));
        for (std::vector<Lesson>::iterator lessonIter = lessons.begin(); lessonIter < lessons.end(); lessonIter++)
        {
            for (int index = lessonIter->start; index <= lessonIter->end; index++)
            {
                std::string content = wks.cell(dayIter->col + std::to_string(index)).value().get<std::string>();
                std::string timeRaw = wks.cell(dayIter->timeCol + std::to_string(lessonIter->start)).value().get<std::string>();

                logger->info("Content Detected: " + content + " with time raw: " + timeRaw);

                if (validate(content))
                {
                    if (isAllLessons)
                    {             
                        all_lessons.push_back(content);
                        all_lessons.unique();
                    }  
                    if (!haveClasses || taken(content))
                    {
                        logger->info("Matched Rule, Adding to Calendar");
                        if (haveDelete)
                        {
                            for (std::vector<std::string>::iterator deleteIter = deletes.begin(); deleteIter < deletes.end(); deleteIter++)
                            {
                                if (content.find(*deleteIter) != std::string::npos)
                                {
                                    content.erase(content.find(*deleteIter), (*deleteIter).length());
                                }
                            }
                        }
                        Event event(content, location_length);
                        event.parse_time(monday + date::days(dayIter->day - 1), timeRaw);
                        events.push_back(event);
                    }
                }
                else
                {
                    logger->info("Invalid Content, Skipping");
                }
            }
        }
    }
}


void Schedule::openDoc(std::string path)
{
    doc.open(path);
}

void Schedule::openWks()
{
    wks = doc.workbook().worksheet(wksName);
}

void Schedule::readConfig(json& config)
{
    logger->info("== Loading Configuration ==");

    logger->info("Reading Exclude");
    if (config.contains("exclude"))
    {
        isExclude = true;

        for (std::string dir: config["exclude"])
        {
            logger->info("Exclude Found: \"" + dir + "\"");
            exclude.push_back(dir);
        }
        exclude = config["exclude"].get<std::vector<std::string>>();
    }
    else
    {
        logger->info("Exclude Not Found");
    }

    logger->info("Reading Exclude_All");
    if (config["exclude_all"] != "null")
    {
        isExcludeAll = true;
        for (std::string dir: config["exclude_all"])
        {
            logger->info("Exclude_All Found: \"" + dir + "\"");
            exclude_all.push_back(dir);
        }
    }
    else
    {
        logger->info("Exclude_All Not Found");
    }

    logger->info("Reading Days");
    for (auto day: config["days"])
    {
        Day d(day["day"], day["col"], day["time"]);
        days.push_back(d);
    }

    if (config.contains("deletes"))
    {
        logger->info("Reading deletes");

        deletes = config["deletes"].get<std::vector<std::string>>();
        haveDelete = true;
    }

    if (config.contains("courses"))
    {
        logger->info("Reading Courses");
        
        haveClasses = true;
        coursesTaken = config["courses"].get<std::vector<std::string>>();
    }

    logger->info("Reading Lessons");
    for (auto lesson: config["lessons"])
    {
        Lesson l(lesson["start"], lesson["end"]);
        lessons.push_back(l);
    }

    if (config.contains("monday"))
    {
        logger->info("Reading Monday");
        std::istringstream is{config["monday"].get<std::string>()};
        is >> date::parse("%F", monday);
    }
    else
    {
        logger->warning("Monday Not Found");
    }

    logger->info("Finding other variables");
    location_length = !config.contains("location_length") ? location_length : config["location_length"].get<int>();
    time_sep = !config.contains("time_sep") ? time_sep : config["time_sep"].get<std::string>();
    hm_sep = !config.contains("hm_sep") ? hm_sep : config["hm_sep"].get<std::string>();
    wksName = !config.contains("worksheet") ? doc.workbook().worksheetNames()[0] : config["worksheet"].get<std::string>();

    logger->info("== Configuration Loaded ==");
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

void Schedule::readArgs(Args args)
{
    if (args.listPath != "")
    {
        isAllLessons = true;
        allLessonsPath = args.listPath;
    }

    if (args.mondayOverride != "")
    {
        logger->info("Overriding Monday");
        std::istringstream is{args.mondayOverride};
        is >> date::parse("%F", monday);
    }
}