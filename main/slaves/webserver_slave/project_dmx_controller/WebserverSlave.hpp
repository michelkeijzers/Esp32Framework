#include <memory>
#include "../../../common/esp_http_server/esp_http_server_if.hpp"
#include "Api/StaticFileHandler.hpp"
#include "./presets/IPresetManager.hpp"

class IEspLittleFs;
class IEspHttpServer;
class IEspNvs;

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
    explicit WebserverSlave(IEspLittleFs& espLittleFs, IEspHttpServer& espHttpServer, IEspNvs& nvsManager);
    ~WebserverSlave();

    void startWebserver();
    void start();
    void stop();

    // Thunk for static file handler
    static esp_err_t static_file_handler_thunk(httpd_req_t *req);

private:
#ifndef UNIT_TEST
    httpd_handle_t server;
#else
    void* server = nullptr;  // Dummy for unit tests
#endif
    IEspLittleFs& espLittleFs_;
    IEspHttpServer& espHttpServer_;
    IEspNvs& nvsManager_;
    
    std::unique_ptr<IPresetManager> presetManager_;

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

    // Non-static member for static file handler
    esp_err_t static_file_handler(httpd_req_t *req);
};
