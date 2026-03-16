#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ...removed component.hpp and slave.hpp...

//#define BUILD_MASTER
#define BUILD_WEBSERVER_SLAVE 1

#if defined(BUILD_MASTER)

#include "common/nodes/master/master.hpp"

#elif defined(BUILD_WEBSERVER_SLAVE)

#include "common/esp/esp_file_systems/EspLittleFs.hpp"
#include "common/esp/esp_http_server/EspHttpServer.hpp"
#include "common/esp/esp_nvs/EspNvs.hpp"
#include "common/esp/esp_logger/EspLogger.hpp"
#include "common/nodes/webserver/webserver_task/DmxControllerWebserver.hpp"
#include "common/nodes/webserver/webserver_task/IDmxControllerWebserver.hpp"
#include "common/nodes/webserver/common/apis/ApiStatus.hpp"
#include "common/nodes/webserver/common/apis/ApiNodes.hpp"
#include "common/nodes/webserver/common/apis/ApiSystem.hpp"
#include "common/nodes/webserver/common/apis/ApiFirmware.hpp"
#include "common/nodes/webserver/common/apis/ApiSecurity.hpp"
#include "common/nodes/webserver/common/apis/ApiLogging.hpp"
#include "common/nodes/webserver/dmx_controller/apis/ApiConfig.hpp"
#include "common/nodes/webserver/dmx_controller/apis/ApiPresets.hpp"
#include "common/nodes/webserver/dmx_controller/apis/ApiPresetValues.hpp"
#include "common/nodes/webserver/dmx_controller/presets/PresetManager.hpp"
#include "common/nodes/webserver/common/IWebserver.hpp"
#include "../tests/mocks/project_dmx_controller/MockDmxControllerWebserver.hpp"

#else 

// Other slaves
#endif // BUILD



// #define BUILD_MASTER 0

extern "C" void app_main(void)
{
#if defined(BUILD_MASTER)
    Master master;
    master.init();
    printf("Built Master component\n");
#elif defined(BUILD_WEBSERVER_SLAVE)
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
    ApiConfig* apiConfig = new ApiConfig(espHttpServer, espNvs);
    ApiPresets* apiPresets = new ApiPresets(espHttpServer, presetManager);
    ApiPresetValues* apiPresetValues = new ApiPresetValues(espHttpServer, presetManager);
    
    // Create DmxControllerWebserver with all dependencies injected
    IDmxControllerWebserver* webserverSlave = new DmxControllerWebserver(
        espLittleFs, espHttpServer, espNvs, espLogger,
        static_cast<ApiStatus&>(apiStatus),
        static_cast<ApiNodes&>(apiNodes),
        static_cast<ApiSystem&>(apiSystem),
        static_cast<ApiFirmware&>(apiFirmware),
        static_cast<ApiSecurity&>(apiSecurity),
        static_cast<ApiLogging&>(apiLogging),
        apiConfig, apiPresets, apiPresetValues, static_cast<IPresetManager&>(presetManager));
    webserverSlave->start();
    printf("Built Webserver component\n");
#else
// Other slaves
#endif // BUILD
}