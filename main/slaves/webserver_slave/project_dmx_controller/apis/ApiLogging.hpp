#pragma once
#include "../../../../common/esp_http_server/esp_http_server_if.hpp"
#include "../../../../common/esp/esp_error_if.hpp"

class IEspHttpServer;

class ApiLogging {
public:
    ApiLogging(IEspHttpServer& espHttpServer);
    ~ApiLogging();

    esp_err_t logging_handler(httpd_req_t *req);

private:
    IEspHttpServer& espHttpServer_;
};
