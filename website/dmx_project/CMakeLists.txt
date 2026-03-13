cmake_minimum_required(VERSION 3.10)
project(dmx_cpp_httplib_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(dmx_cpp_httplib_server main.cpp)

# Include current directory for headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
