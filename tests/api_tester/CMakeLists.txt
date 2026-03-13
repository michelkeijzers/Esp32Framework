cmake_minimum_required(VERSION 3.16)
project(api_tester)

set(CMAKE_CXX_STANDARD 17)



add_executable(api_tester
    test_main.cpp
    MockEspHttpServer.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/ApiPresets.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/ApiConfig.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/ApiStatus.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/ApiPresetValues.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/ApiNodes.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/ApiSystem.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/ApiFirmware.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/ApiSecurity.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/ApiLogging.cpp
)

# Define UNIT_TEST for test build
target_compile_definitions(api_tester PRIVATE UNIT_TEST)

# Add include directories for main/esp and project_dmx_controller
target_include_directories(api_tester PRIVATE
    .
    ../../main/esp
    ../../main/slaves/webserver_slave/project_dmx_controller
)

# Add additional include directories if needed
# target_include_directories(api_tester PRIVATE ../../main/slaves/webserver_slave/project_dmx_controller)

# Link libraries if your handlers require them
# target_link_libraries(api_tester ...)
