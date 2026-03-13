
#include "../esp/IEspHttpServer.hpp"
#include "../esp/esp_http_server_if.hpp"

class ApiConfig;
class ApiPresets;
class ApiStatus;

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
    ApiStatus* apiStatus_;

    void register_endpoints();
};
