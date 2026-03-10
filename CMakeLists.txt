cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "my-esp-idf-project")
set(PROJECT_VERSION "1.0")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(${PROJECT_NAME}) 

file(GLOB_RECURSE SRC_FILES "main/*.cpp")

