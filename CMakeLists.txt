cmake_minimum_required (VERSION 2.8)
project (centai)

set (dehax_VERSION_MAJOR 0)
set (dehax_VERSION_MINOR 1)
add_definitions(-std=c++11)

include_directories(inc)
file(GLOB SRCS src/*.cpp)

add_executable(centai ${SRCS}) 

install (TARGETS centai DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
