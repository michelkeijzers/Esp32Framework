cmake_minimum_required(VERSION 3.16)
project(api_tester)

set(CMAKE_CXX_STANDARD 17)

add_executable(api_tester
    test_main.cpp
    ../mocks/esp32/MockEspHttpServer.cpp
    ../mocks/esp32/MockEspNow.cpp
    ../mocks/esp32/MockEspNvs.cpp
    ../mocks/esp32/MockEspLogger.cpp
    apis/ApiPresetsTests.cpp
    apis/ApiStatusTests.cpp
    apis/ApiConfigTests.cpp
    apis/ApiFirmwareTests.cpp
    apis/ApiLoggingTests.cpp
    apis/ApiNodesTests.cpp
    apis/ApiPresetValuesTests.cpp
    apis/ApiSecurityTests.cpp
    apis/ApiSystemTests.cpp
    ../../main/projects/dmx_controller/http_task/DmxControllerHttpTask.cpp
    ../../main/common/nodes/webserver/dmx_controller/apis/ApiPresets.cpp
    ../../main/common/nodes/webserver/dmx_controller/apis/ApiConfig.cpp
    ../../main/common/nodes/webserver/http_task/apis/ApiStatus.cpp
    ../../main/common/nodes/webserver/dmx_controller/apis/ApiPresetValues.cpp
    ../../main/common/nodes/webserver/http_task/apis/ApiNodes.cpp
    ../../main/common/nodes/webserver/http_task/apis/ApiSystem.cpp
    ../../main/common/nodes/webserver/http_task/apis/ApiFirmware.cpp
    ../../main/common/nodes/webserver/http_task/apis/ApiSecurity.cpp
    ../../main/common/nodes/webserver/http_task/apis/ApiLogging.cpp
    ../../main/common/nodes/webserver/http_task/apis/ApiResponse.cpp
    ../../main/common/nodes/webserver/http_task/apis/ApiValidator.cpp
    ../../main/common/esp/esp_http_server/EspHttpServer.cpp
    ../../main/common/nodes/webserver/dmx_controller/presets/PresetManager.cpp
    ../../main/common/nodes/webserver/webserver_task/Webserver.cpp
    ../../main/projects/dmx_controller/http_task/DmxControllerHttpTask.cpp
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
    ../../main/common/nodes/webserver/dmx_controller
    ../../main/common/nodes/webserver/webserver_task
    ../../main/common/nodes/webserver/http_task/apis
    ../../main/common/nodes/webserver/dmx_controller/apis
    ../../main/common
    ../../main/common/nvs
    ../../main/common/esp/esp_logger
    ../../main/common/esp/esp_http_server
    ../../main/common/esp/esp_now
    ../../main/common/esp/esp_nvs
)

# Add additional include directories if needed
# target_include_directories(api_tester PRIVATE ../../main/slaves/webserver_slave/dmx_controller)

# Link libraries if your handlers require them
# target_link_libraries(api_tester ...)
