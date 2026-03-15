cmake_minimum_required(VERSION 3.16)
project(api_tester)

set(CMAKE_CXX_STANDARD 17)

add_executable(api_tester
    test_main.cpp
    mocks/infrastructure/MockEspHttpServer.cpp
    mocks/infrastructure/MockEspNowHandler.cpp
    mocks/infrastructure/MockEspNvs.cpp
    mocks/infrastructure/MockEspLogger.cpp
    apis/ApiPresetsTests.cpp
    apis/ApiStatusTests.cpp
    apis/ApiConfigTests.cpp
    apis/ApiFirmwareTests.cpp
    apis/ApiLoggingTests.cpp
    apis/ApiNodesTests.cpp
    apis/ApiPresetValuesTests.cpp
    apis/ApiSecurityTests.cpp
    apis/ApiSystemTests.cpp
    ../../main/slaves/webserver_slave/dmx_controller/DmxControllerWebserverSlave.cpp
    ../../main/slaves/webserver_slave/dmx_controller/apis/ApiPresets.cpp
    ../../main/slaves/webserver_slave/dmx_controller/apis/ApiConfig.cpp
    ../../main/slaves/webserver_slave/common/apis/ApiStatus.cpp
    ../../main/slaves/webserver_slave/dmx_controller/apis/ApiPresetValues.cpp
    ../../main/slaves/webserver_slave/common/apis/ApiNodes.cpp
    ../../main/slaves/webserver_slave/common/apis/ApiSystem.cpp
    ../../main/slaves/webserver_slave/common/apis/ApiFirmware.cpp
    ../../main/slaves/webserver_slave/common/apis/ApiSecurity.cpp
    ../../main/slaves/webserver_slave/common/apis/ApiLogging.cpp
    ../../main/slaves/webserver_slave/common/apis/ApiResponse.cpp
    ../../main/slaves/webserver_slave/common/apis/ApiValidator.cpp
    ../../main/common/esp_http_server/EspHttpServer.cpp
    ../../main/common/esp_now/EspNowHandler.cpp
    ../../main/slaves/webserver_slave/dmx_controller/presets/PresetManager.cpp
    ../../main/slaves/webserver_slave/common/WebserverSlave.cpp
    # ../../main/common/esp_nvs/EspNvs.cpp
)

set_property(TARGET api_tester PROPERTY CXX_STANDARD 20)

# Define UNIT_TEST for test build
target_compile_definitions(api_tester PRIVATE UNIT_TEST)

# Allow multiple symbol definitions for ESP IDF duplicate symbols in test build
if(MSVC)
    target_link_options(api_tester PRIVATE /FORCE:MULTIPLE)
endif()

# Add include directories for main/esp, dmx_controller, and Api subdirectory
target_include_directories(api_tester PRIVATE
    .
    ./api
    ./mock
    ../../main/esp
    ../../main/slaves/webserver_slave/dmx_controller
    ../../main/slaves/webserver_slave/common
    ../../main/slaves/webserver_slave/common/apis
    ../../main/slaves/webserver_slave/dmx_controller/apis
    ../../main/common
    ../../main/common/nvs
    ../../main/common/esp_logger
    ../../main/common/esp_http_server
    ../../main/common/esp_now
    ../../main/common/esp_nvs
)

# Add additional include directories if needed
# target_include_directories(api_tester PRIVATE ../../main/slaves/webserver_slave/dmx_controller)

# Link libraries if your handlers require them
# target_link_libraries(api_tester ...)
