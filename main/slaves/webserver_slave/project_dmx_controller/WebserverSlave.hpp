
#include "../../../esp/IEspHttpServer.hpp"
#include "../../../esp/esp_http_server_if.hpp"

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
    httpd_handle_t server;
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

    void register_endpoints();
};
