cmake_minimum_required(VERSION 2.8.8)
project(WebServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -lboost_system -pthread")

include_directories(src)
#include_directories(tests)
include_directories(lib)

add_subdirectory(src)
#add_subdirectory(tests)
