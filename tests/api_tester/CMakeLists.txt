cmake_minimum_required(VERSION 3.16)
project(api_tester)

set(CMAKE_CXX_STANDARD 17)

add_executable(api_tester
    test_main.cpp
    MockEspHttpServer.cpp
    MockEspNowHandler.cpp
    MockEspNvs.cpp
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
    ../../main/slaves/webserver_slave/project_dmx_controller/api/ApiPresets.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/api/ApiConfig.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/api/ApiStatus.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/api/ApiPresetValues.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/api/ApiNodes.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/api/ApiSystem.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/api/ApiFirmware.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/api/ApiSecurity.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/api/ApiLogging.cpp
    ../../main/common/esp_http_server/EspHttpServer.cpp
    ../../main/common/esp_now/EspNowHandler.cpp
    ../../main/slaves/webserver_slave/project_dmx_controller/presets/PresetManager.cpp
    # ../../main/common/esp_nvs/EspNvs.cpp
)

set_property(TARGET api_tester PROPERTY CXX_STANDARD 20)

# Define UNIT_TEST for test build
target_compile_definitions(api_tester PRIVATE UNIT_TEST)

# Add include directories for main/esp, project_dmx_controller, and Api subdirectory
target_include_directories(api_tester PRIVATE
    .
    ../../main/esp
    ../../main/slaves/webserver_slave/project_dmx_controller
    ../../main/slaves/webserver_slave/project_dmx_controller/Api
    ../../main/common
    ../../main/common/nvs
    ../../main/common/logging
    ../../main/common/esp_http_server
    ../../main/common/esp_now
    ../../main/common/esp_nvs
)

# Add additional include directories if needed
# target_include_directories(api_tester PRIVATE ../../main/slaves/webserver_slave/project_dmx_controller)

# Link libraries if your handlers require them
# target_link_libraries(api_tester ...)
