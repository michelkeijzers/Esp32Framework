#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// DEFINES FOR THE PROJECT AND NODE TO BUILD
#define BUILD_PROJECT_DMX_CONTROLLER

#define BUILD_WEBSERVER_NODE
// #define BUILD_MASTER_NODE
// #define BUILD_DMX_NODE

#if defined(BUILD_WEBSERVER_NODE)

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

#if defined(BUILD_PROJECT_DMX_CONTROLLER)

#include "projects/dmx_controller/http_task/apis/ApiConfig.hpp"
#include "projects/dmx_controller/http_task/apis/ApiPresets.hpp"
#include "projects/dmx_controller/http_task/apis/ApiPresetValues.hpp"
#include "projects/dmx_controller/presets_task/PresetManager.hpp"
#include "projects/dmx_controller/service_locator/DmxServiceLocator.hpp"
#include "projects/dmx_controller/dmx_controller_task/DmxControllerTask.hpp"

#elif defined(BUILD_PROJECT_OTHER)

#endif // BUILD_PROJECT

#elif defined(BUILD_MASTER_NODE)

#include "common/nodes/master/master.hpp"

#elif defined(BUILD_GPIO_NODE)

#elif defined(BUILD_DMX_NODE)

#endif // NODE_TO_BUILD

extern "C"
{
    void app_main(void)
    {
#if defined(BUILD_WEBSERVER_NODE)

#if defined(BUILD_PROJECT_DMX_CONTROLLER)

    // Create service locator (all dependencies are created internally)
    DmxServiceLocator serviceLocator;

    // Create and start main controller task
    DmxControllerTask controllerTask(serviceLocator);
    esp_err_t err = controllerTask.init();
    if (err != ESP_OK)
    {
        printf("Failed to initialize DmxControllerTask: %d\n", err);
        return;
    }

    err = controllerTask.start();
    if (err != ESP_OK)
    {
        printf("Failed to start DmxControllerTask: %d\n", err);
        return;
    }

#elif defined(BUILD_PROJECT_OTHER)
#endif // BUILD_PROJECT

#elif defined(BUILD_MASTER)
    Master master;
    master.init();
    printf("Built Master component\n");
#else
// Other nodes
#endif // BUILD
}
}