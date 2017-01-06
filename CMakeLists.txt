cmake_minimum_required(VERSION 3.6)
project(WebServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src)
include_directories(tests)
include_directories(lib)

add_subdirectory(src)
add_subdirectory(tests)

# Boost.Asio
set(BOOST_COMPONENTS system thread filesystem date_time)
find_package(Boost 1.54.0 COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})
