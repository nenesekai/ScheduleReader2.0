add_library(args args.h args.cpp)
add_library(schedule schedule.h schedule.cpp)
add_library(logger logger.h logger.cpp)
add_library(calendar calendar.h calendar.cpp)
target_link_libraries(calendar PRIVATE date-tz)
target_link_libraries(schedule 
    PRIVATE nlohmann_json::nlohmann_json OpenXLSX-static date-tz calendar)

add_executable(main main.cpp)
target_link_libraries(main 
    PRIVATE nlohmann_json::nlohmann_json OpenXLSX-static args calendar schedule logger date-tz)