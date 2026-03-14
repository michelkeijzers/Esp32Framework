
#include "../../../esp/IEspHttpServer.hpp"
#include "Api/StaticFileHandler.hpp"

#ifndef UNIT_TEST
#include "../../../esp/esp_http_server_if.hpp"
#include "esp_spiffs.h"
#ifdef CONFIG_LITTLEFS_FOR_IDF_VFS
#include "esp_littlefs.h"
#endif
#endif

class ApiConfig;
class ApiPresets;
class ApiPresetValues;
class ApiStatus;
class ApiNodes;
class ApiSystem;
class ApiFirmware;
class ApiSecurity;
class ApiLogging;

class WebserverSlave
{
public:
    explicit WebserverSlave(IEspHttpServer& espHttpServer);
    ~WebserverSlave();

    void startWebserver();
    void start();
    void stop();

private:
#ifndef UNIT_TEST
    httpd_handle_t server;
#else
    void* server = nullptr;  // Dummy for unit tests
#endif
    IEspHttpServer& espHttpServer_;

    ApiConfig* apiConfig_;
    ApiPresets* apiPresets_;
    ApiPresetValues* apiPresetValues_;
    ApiStatus* apiStatus_;
    ApiNodes* apiNodes_;
    ApiSystem* apiSystem_;
    ApiFirmware* apiFirmware_;
    ApiSecurity* apiSecurity_;
    ApiLogging* apiLogging_;

    void mount_littlefs();
    void register_static_file_handler();
    void register_endpoints();
    void register_endpoints_esp32();
    void register_endpoints_test();
};
