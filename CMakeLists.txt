cmake_minimum_required(VERSION 3.0.0)
project(ScheduleReader VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(IGNORE_ME ${CMAKE_C_COMPILER})

add_subdirectory(lib)
add_subdirectory(src)
