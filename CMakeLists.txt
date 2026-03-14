cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "my-esp-idf-project")
set(PROJECT_VERSION "1.0")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(${PROJECT_NAME}) 

file(GLOB_RECURSE SRC_FILES "main/*.cpp")

# Custom target to build the website with Vite
add_custom_target(build_website
    COMMAND ${CMAKE_COMMAND} -E echo "Building website with Vite..."
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_SOURCE_DIR}/website/dmx_project/dist"
    COMMAND npm --prefix "${CMAKE_SOURCE_DIR}/website/dmx_project" run build
    COMMENT "Building and minifying website with Vite"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/website/dmx_project"
)


# Custom target to create the LittleFS image after website build
# NOTE: If mklittlefs is not available, the script will print a warning
# but continue gracefully. The ESP32 will format the partition on first boot.
add_custom_target(create_littlefs_image ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Creating LittleFS image..."
    COMMAND ${CMAKE_COMMAND} -E env IDF_PATH=$ENV{IDF_PATH} python "${CMAKE_SOURCE_DIR}/website/dmx_project/create_littlefs_image.py"
    DEPENDS build_website
    COMMENT "Creating LittleFS image from website dist folder"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Make the main build depend on create_littlefs_image (which depends on build_website)
add_dependencies(${PROJECT_NAME}.elf create_littlefs_image)

# Custom target to build and run API tester
add_custom_target(run_api_tester ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Building and running API tester..."
    COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_SOURCE_DIR}/tests/api_tester" cmake --build build --config Debug
    COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_SOURCE_DIR}/tests/api_tester/build/Debug" ./api_tester.exe
    COMMENT "Build and run API tester after main build"
    DEPENDS ${PROJECT_NAME}.elf
)

