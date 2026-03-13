
#include "../esp/IEspHttpServer.hpp"
#include "../esp/esp_http_server_if.hpp"

class WebserverSlave
{
public:
    // Inject IEspHttpServer via constructor
    explicit WebserverSlave(IEspHttpServer& espHttpServer);
    ~WebserverSlave();

    void startWebserver();
    void start();
    void stop();

private:
    httpd_handle_t server;
    IEspHttpServer& espHttpServer_;

    void register_endpoints();
};
