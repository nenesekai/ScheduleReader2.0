cmake_minimum_required(VERSION 3.0.0)
project(ScheduleReader VERSION 2.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
