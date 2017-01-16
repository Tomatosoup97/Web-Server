cmake_minimum_required(VERSION 2.8.8)
project(async_http_client)


set(HEADER_FILES )
set(SOURCE_FILES client_runner.hpp async_client.hpp)

add_executable(async_http_client ${SOURCE_FILES})

target_link_libraries(async_http_client ${CMAKE_THREAD_LIBS_INIT})

# Boost.Asio
set(BOOST_COMPONENTS system thread filesystem date_time)
find_package(Boost 1.54.0 COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})
link_directories(async_http_client ${Boost_LIBRARY_DIRS})
target_link_libraries(async_http_client ${Boost_LIBRARIES})
