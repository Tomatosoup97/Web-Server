cmake_minimum_required(VERSION 2.8.8)
project(web_server)


set(HEADER_FILES )
set(SOURCE_FILES main.cpp async_client.hpp exceptions.hpp)

add_executable(web_server ${SOURCE_FILES})

include_directories(client)
add_subdirectory(client)

find_package(Threads REQUIRED)
target_link_libraries(web_server ${CMAKE_THREAD_LIBS_INIT})

# Boost.Asio
set(BOOST_COMPONENTS system thread filesystem date_time)
find_package(Boost 1.54.0 COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})
link_directories(web_server ${Boost_LIBRARY_DIRS})
target_link_libraries(web_server ${Boost_LIBRARIES})
