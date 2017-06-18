cmake_minimum_required (VERSION 2.8)
project (testapp)

set (testapp_VERSION_MAJOR 0)
set (testapp_VERSION_MINOR 1)
add_definitions(-std=c++11)

include_directories(inc)
file(GLOB SRCS testapp/*.cpp)

add_executable(testapp ${SRCS}) 

install (TARGETS testapp DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
