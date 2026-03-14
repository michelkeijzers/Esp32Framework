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
#include "slaves/webserver_slave/project_dmx_controller/WebserverSlave.hpp"
#include "common/esp_nvs/EspNvs.hpp"

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
    EspLittleFs espLittleFs;
    EspHttpServer espHttpServer;
    EspNvs espNvs;
    WebserverSlave webserverSlave(espLittleFs, espHttpServer, espNvs);
    webserverSlave.start();
    printf("Built Webserver Slave component\n");
#else
// Other slaves
#endif // BUILD
}