#include "calendar.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

Event::Event(std::string content, int location_length)
{
    summary = location_length == 0 ? content : content.substr(0, content.find_last_of('-'));
    location = location_length == 0 ? "" : content.substr(content.size() - location_length, location_length);
}

void Event::write(std::ofstream& ofs)
{
    ofs << "BEGIN:VEVENT" << std::endl;

    if (summary != "") ofs << "SUMMARY:" << summary << std::endl;
    if (dtstart != "") ofs << "DTSTART:" << dtstart << std::endl;
    if (dtend != "") ofs << "DTEND:" << dtend << std::endl;
    if (location != "") ofs << "LOCATION:" << location << std::endl;
    if (description != "") ofs << "DESCRIPTION:" << description << std::endl;

    ofs << "STATUS:CONFIRMED" << std::endl;

    ofs << "END:VEVENT" << std::endl;
}

std::string Calendar::todt(date::year_month_day date, Time time)
{
    return date::format("%Y%m%d", date) + "T" + time.to_string() + "Z";
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

Time::Time(std::string content, std::string hs_sep)
{
    hour = 0;
    minute = 0;
    second = 0;
    from_string(content, hs_sep);
}

void Time::from_string(std::string content, std::string hm_sep)
{
    hour = stoi(content.substr(0, content.find(hm_sep)));
    minute = stoi(content.substr(content.find(hm_sep) + hm_sep.length(), content.length() - content.find(hm_sep) - hm_sep.length()));
}

std::string Time::twodigit(int num)
{
    if (num < 10)
    {
        return "0" + std::to_string(num);
    }
    else
    {
        return std::to_string(num);
    }
}

std::string Time::to_string()
{
    return twodigit(hour) + twodigit(minute) + twodigit(second);
}

Time_Interval::Time_Interval(std::string content, std::string time_sep, std::string hm_sep)
{
    start.from_string(content.substr(0, content.find(time_sep)), hm_sep);
    end.from_string(content.substr(content.find(time_sep) + 1, content.length() - content.find(time_sep) - 1), hm_sep);
}