#include "calendar.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "date/tz.h"

Event::Event(std::string content, int location_length)
{
    summary = location_length == 0 ? content : content.substr(0, content.find_last_of('-'));
    location = location_length == 0 ? "" : content.substr(content.size() - location_length, location_length);
}

void Event::write(std::ofstream& ofs)
{
    ofs << "BEGIN:VEVENT" << std::endl;

    if (summary != "") ofs << "SUMMARY:" << summary << std::endl;
    ofs << "DTSTART:" << date::format(this->format, date::make_zoned(outputTimeZone, timeStart)) << std::endl;
    ofs << "DTEND:" << date::format(this->format, date::make_zoned(outputTimeZone, timeEnd)) << std::endl;
    if (location != "") ofs << "LOCATION:" << location << std::endl;
    if (description != "") ofs << "DESCRIPTION:" << description << std::endl;

    ofs << "STATUS:CONFIRMED" << std::endl;

    ofs << "END:VEVENT" << std::endl;
}

void Event::parse_time(date::local_days date, std::string timeRaw, std::string time_sep, std::string hm_sep)
{
    std::string timeRawStart = timeRaw.substr(0, timeRaw.find(time_sep));
    std::string timeRawEnd = timeRaw.substr(timeRaw.find(time_sep) + 1, timeRaw.length() - timeRaw.find(time_sep) - 1);

    timeStart = date::make_zoned(timezone, date + std::chrono::hours(std::stoi(timeRawStart.substr(0, timeRawStart.find(hm_sep)))) + std::chrono::minutes(std::stoi(timeRawStart.substr(timeRawStart.find(hm_sep) + 1, timeRawStart.length() - timeRawStart.find(hm_sep) - 1))));
    timeEnd = date::make_zoned(timezone, date + std::chrono::hours(std::stoi(timeRawEnd.substr(0, timeRawEnd.find(hm_sep)))) + std::chrono::minutes(std::stoi(timeRawEnd.substr(timeRawEnd.find(hm_sep) + 1, timeRawEnd.length() - timeRawEnd.find(hm_sep) - 1))));
}

void Calendar::to_ical(std::string path)
{
    std::ofstream ical(path);
    ical << "BEGIN:VCALENDAR\n";

    ical << "PRODID:-//Asiimoviet//Schedule Reader 2.0//EN" << std::endl;
    ical << "VERSION:2.0" << std::endl;
    ical << "CALSCALE:GREGORIAN" << std::endl;
    ical << "METHOD:PUBLISH" << std::endl;

    ical << "X-WR-CALNAME:" << calname << "\n";
    ical << "X-WR-TIMEZONE:" << timezone << "\n";

    for (std::vector<Event>::iterator eventIter = events.begin(); eventIter < events.end(); eventIter++)
    {
        eventIter->write(ical);
    }

    ical << "END:VCALENDAR\n";
}
