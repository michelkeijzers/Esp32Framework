#pragma once
#include "../../../../esp/esp_http_server_if.hpp"
#include "../../../../esp/esp_error_if.hpp"

class IEspHttpServer;

class ApiSystem {
public:
    ApiSystem(IEspHttpServer& espHttpServer);
    ~ApiSystem();

    esp_err_t reboot_handler(httpd_req_t *req);
    esp_err_t factory_reset_handler(httpd_req_t *req);

private:
    IEspHttpServer& espHttpServer_;
};
