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
#include "slaves/webserver_slave/project_dmx_controller/webserver_slave.hpp"
#else 
// Other slaves
#endif // BUILD

#include "esp/IEspHttpServer.hpp"


// #define BUILD_MASTER 0

extern "C" void app_main(void)
{
#if defined(BUILD_MASTER)
    Master master;
    master.init();
    printf("Built Master component\n");
#elif defined(BUILD_WEBSERVER_SLAVE)
    EspHttpServer espHttpServer;    
    WebserverSlave webserverSlave(espHttpServer);
    webserverSlave.start();
    printf("Built Webserver Slave component\n");
#else
// Other slaves
#endif // BUILD
}