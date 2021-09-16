#include <iostream>

#include "calendar.h"
#include "date/tz.h"

int main()
{
    Event event("test");
    auto d = date::local_days{date::April/30/2004};
    event.convertToTime(d, "8:10-9:10");
    std::cout << event.dtstart << std::endl << event.dtend << std::endl;
    return 0;
}