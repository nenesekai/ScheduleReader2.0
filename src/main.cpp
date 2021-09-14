#include <iostream>
#include <string>
#include <list>
#include "nlohmann/json.hpp"
#include "OpenXLSX.hpp"
#include "args.h"
#include "schedule.h"
#include "logger.h"
#include "calendar.h"
#include "date/tz.h"

using nlohmann::json;
using namespace OpenXLSX;

int main(int argc, char **argv)
{
    // Process Arguments
    Args args;
    args.read(argc, argv);
    try
    {
        args.validate();
    }
    catch (const std::invalid_argument &e)
    {
        err(e.what());
    }

    // Read Config File
    std::ifstream configFile(args.configPath);
    json config;
    configFile >> config;

    // Handle with Schedule
    Schedule schedule;
    schedule.readFromFile(args.xlsxPath, config["worksheet"]);
    schedule.readConfig(config);

    Calendar calendar;
    calendar.events = schedule.parseEvents();
    schedule.exportAllLessons("./all.txt");
    calendar.to_ical(args.outputPath);
    return 0;
}
