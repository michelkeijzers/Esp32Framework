cmake_minimum_required(VERSION 3.16)
project(api_tester)

set(CMAKE_CXX_STANDARD 17)



add_executable(api_tester
    test_main.cpp
    MockEspHttpServer.cpp
    ApiPresetsTests.cpp
    ApiStatusTests.cpp
    ApiConfigTests.cpp
    ApiFirmwareTests.cpp
    ApiLoggingTests.cpp
    ApiNodesTests.cpp
    ApiPresetValuesTests.cpp
    ApiSecurityTests.cpp
    ApiSystemTests.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/WebserverSlave.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/Api/ApiPresets.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/Api/ApiConfig.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/Api/ApiStatus.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/Api/ApiPresetValues.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/Api/ApiNodes.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/Api/ApiSystem.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/Api/ApiFirmware.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/Api/ApiSecurity.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/Api/ApiLogging.cpp
)

# Define UNIT_TEST for test build
target_compile_definitions(api_tester PRIVATE UNIT_TEST)

# Add include directories for main/esp, project_dmx_controller, and Api subdirectory
target_include_directories(api_tester PRIVATE
    .
    ../../main/esp
    ../../main/slaves/webserver_slave/project_dmx_controller
    ../../main/slaves/webserver_slave/project_dmx_controller/Api
)

# Add additional include directories if needed
# target_include_directories(api_tester PRIVATE ../../main/slaves/webserver_slave/project_dmx_controller)

# Link libraries if your handlers require them
# target_link_libraries(api_tester ...)
