
#pragma once
#include "../../../esp/esp_http_server_if.hpp"
#include "../../../esp/esp_error_if.hpp"

class IEspHttpServer;

class ApiStatus {
public:
    ApiStatus(IEspHttpServer& espHttpServer);
    ~ApiStatus();

    esp_err_t get_status_handler(httpd_req_t *req);

private:
    IEspHttpServer& espHttpServer_;
};
