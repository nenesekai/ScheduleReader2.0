add_library(args include/args.h sources/args.cpp)
add_library(schedule include/schedule.h sources/schedule.cpp)
add_library(logger include/logger.h sources/logger.cpp)
add_library(calendar include/calendar.h sources/calendar.cpp)

include_directories(include)

target_link_libraries(args PRIVATE logger)
target_link_libraries(calendar PRIVATE date-tz)
target_link_libraries(schedule 
    PRIVATE nlohmann_json::nlohmann_json OpenXLSX-static date-tz calendar logger)

add_executable(main main.cpp)
add_executable(test test.cpp)
target_link_libraries(main 
    PRIVATE nlohmann_json::nlohmann_json OpenXLSX-static args calendar schedule logger date-tz)
target_link_libraries(test
    PRIVATE nlohmann_json::nlohmann_json OpenXLSX-static args calendar schedule logger date-tz)
set_target_properties(main PROPERTIES OUTPUT_NAME "schedule")