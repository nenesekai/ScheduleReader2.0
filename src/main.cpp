#include <iostream>
#include <list>
#include <string>

#include "OpenXLSX.hpp"
#include "args.h"
#include "calendar.h"
#include "date/tz.h"
#include "logger.h"
#include "nlohmann/json.hpp"
#include "schedule.h"

int main(int argc, char** argv)
{
    Logger* logger = new Logger();

    // Process Arguments
    Args args(logger);
    args.read(argc, argv);
    logger->report();
    try {
        args.validate();
    } catch (const std::invalid_argument& e) {
        logger->err(e.what());
        std::cout << "Use schedule --help for usage and options" << std::endl;
        exit(0);
    }

    // Read Config File
    std::ifstream configFile(args.configPath);
    nlohmann::json config;
    configFile >> config;

    // Handle with Schedule
    Schedule schedule(logger);
    schedule.openDoc(args.xlsxPath);
    schedule.readConfig(config);
    schedule.openWks();
    schedule.readArgs(args);
    schedule.parseEvents();

    if (args.outputPath != "") {
        Calendar calendar;
        calendar.events = schedule.events;
        calendar.to_ical(args.outputPath);
    }

    if (args.listPath != "") {
        schedule.exportAllLessons(args.listPath);
    }
    
    return 0;
}
