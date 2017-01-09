cmake_minimum_required(VERSION 3.6)
project(web_server)

set(HEADER_FILES )
set(SOURCE_FILES main.cpp async_client.hpp exceptions.hpp)
add_executable(web_server ${SOURCE_FILES})
