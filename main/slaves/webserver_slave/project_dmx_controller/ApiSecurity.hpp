#pragma once
#include "../../../esp/esp_http_server_if.hpp"
#include "../../../esp/esp_error_if.hpp"

class IEspHttpServer;

class ApiSecurity {
public:
    ApiSecurity(IEspHttpServer& espHttpServer);
    ~ApiSecurity();

    esp_err_t esp_now_key_handler(httpd_req_t *req);
    esp_err_t wifi_password_handler(httpd_req_t *req);

private:
    IEspHttpServer& espHttpServer_;
};
