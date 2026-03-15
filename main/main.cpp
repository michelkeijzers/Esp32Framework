#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "common/component.hpp"
#include "common/slave.hpp"

//#define BUILD_MASTER
#define BUILD_WEBSERVER_SLAVE 1

#if defined(BUILD_MASTER)

#include "master/master.hpp"

#elif defined(BUILD_WEBSERVER_SLAVE)

#include "common/esp_file_systems/EspLittleFs.hpp"
#include "common/esp_http_server/EspHttpServer.hpp"
#include "common/esp_nvs/EspNvs.hpp"
#include "common/esp_logger/EspLogger.hpp"
#include "slaves/webserver_slave/dmx_controller/DmxControllerWebserverSlave.hpp"
#include "slaves/webserver_slave/common/apis/ApiStatus.hpp"
#include "slaves/webserver_slave/common/apis/ApiNodes.hpp"
#include "slaves/webserver_slave/common/apis/ApiSystem.hpp"
#include "slaves/webserver_slave/common/apis/ApiFirmware.hpp"
#include "slaves/webserver_slave/common/apis/ApiSecurity.hpp"
#include "slaves/webserver_slave/common/apis/ApiLogging.hpp"
#include "slaves/webserver_slave/dmx_controller/apis/ApiConfig.hpp"
#include "slaves/webserver_slave/dmx_controller/apis/ApiPresets.hpp"
#include "slaves/webserver_slave/dmx_controller/apis/ApiPresetValues.hpp"
#include "slaves/webserver_slave/dmx_controller/presets/PresetManager.hpp"

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
    
    // Create WebserverSlave with all dependencies injected
    DmxControllerWebserverSlave webserverSlave(espLittleFs, espHttpServer, espNvs, espLogger,
                                               static_cast<ApiStatus&>(apiStatus),
                                               static_cast<ApiNodes&>(apiNodes),
                                               static_cast<ApiSystem&>(apiSystem),
                                               static_cast<ApiFirmware&>(apiFirmware),
                                               static_cast<ApiSecurity&>(apiSecurity),
                                               static_cast<ApiLogging&>(apiLogging),
                                               apiConfig, apiPresets, apiPresetValues, static_cast<IPresetManager&>(presetManager));
    webserverSlave.start();
    printf("Built Webserver Slave component\n");
#else
// Other slaves
#endif // BUILD
}