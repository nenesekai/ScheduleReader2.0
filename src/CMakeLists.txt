add_executable(main main.cpp)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json OpenXLSX-static)
set_target_properties(main PROPERTIES OUTPUT_NAME "schedule")