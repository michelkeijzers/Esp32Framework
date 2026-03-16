#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "common/context/Contexts.hpp"

// Select project to build
#define BUILD_PROJECT_DMX_CONTROLLER 1

// Select Node to build

//#define BUILD_MASTER_NODE 1
#define BUILD_WEBSERVER_NODE 2
// #define BUILD_GPIO_NODE 3
// #define BUILD_DMX_NODE 4


#if defined(BUILD_MASTER_NODE)

#include "common/nodes/master/master.hpp"

#elif defined(BUILD_WEBSERVER_NODE)

#include "common/esp/esp_file_systems/EspLittleFs.hpp"
#include "common/esp/esp_http_server/EspHttpServer.hpp"
#include "common/esp/esp_nvs/EspNvs.hpp"
#include "common/esp/esp_logger/EspLogger.hpp"
#include "common/nodes/webserver/http_task/apis/ApiStatus.hpp"
#include "common/nodes/webserver/http_task/apis/ApiNodes.hpp"
#include "common/nodes/webserver/http_task/apis/ApiSystem.hpp"
#include "common/nodes/webserver/http_task/apis/ApiFirmware.hpp"
#include "common/nodes/webserver/http_task/apis/ApiSecurity.hpp"
#include "common/nodes/webserver/http_task/apis/ApiLogging.hpp"
#include "common/nodes/webserver/http_task/IApiServer.hpp"

#ifdef BUILD_PROJECT_DMX_CONTROLLER

#include "projects/dmx_controller/http_task/DmxControllerHttpTask.hpp"
#include "projects/dmx_controller/http_task/IDmxControllerHttpTask.h"
#include "projects/dmx_controller/http_task/apis/ApiConfig.hpp"
#include "projects/dmx_controller/http_task/apis/ApiPresets.hpp"
#include "projects/dmx_controller/http_task/apis/ApiPresetValues.hpp"
#include "projects/dmx_controller/presets_task/PresetManager.hpp"

#elif // Other projects 

#endif // BUILD_PROJECT

#elif defined(BUILD_GPIO_NODE)

#elif defined(BUILD_DMX_NODE)

#endif // NODE_TO_BUILD

// #define BUILD_MASTER 0

extern "C" void app_main(void)
{
#if defined(BUILD_MASTER)
    Master master;
    master.init();
    printf("Built Master component\n");
#elif defined(BUILD_WEBSERVER_NODE)
    // Create infrastructure services
    EspLittleFs espLittleFs;
    EspHttpServer espHttpServer;
    EspNvs espNvs;
    EspLogger espLogger;

    // Create generic API instances
    ApiStatus apiStatus(espHttpServer);
    ApiNodes apiNodes(espHttpServer);
    ApiSystem apiSystem(espHttpServer);
    ApiFirmware apiFirmware(espHttpServer);
    ApiSecurity apiSecurity(espHttpServer);
    ApiLogging apiLogging(espHttpServer);
    
    // Create DMX-specific instances
    PresetManager presetManager(espNvs);

    ApiConfig apiConfig(espHttpServer, espNvs);
    ApiPresets apiPresets(espHttpServer, presetManager);
    ApiPresetValues apiPresetValues(espHttpServer, presetManager);

    // Create DmxControllerHttpTask with all dependencies injected
    EspContexts espContexts{espLittleFs, espHttpServer, espNvs, espLogger};
    CommonApiContexts commonApiContexts{apiStatus, apiNodes, apiSystem, apiFirmware, apiSecurity, apiLogging};
    Contexts contexts{espContexts, commonApiContexts};

    DmxControllerHttpTask webserver(
        DmxControllerHttpTask(contexts, apiConfig, apiPresets, apiPresetValues, presetManager));
    webserver.start();
    printf("Built Webserver component\n");
#else
// Other nodes
#endif // BUILD
}