
#pragma once
#include "../../../esp/esp_http_server_if.hpp"
#include "../../../esp/esp_error_if.hpp"


class IEspHttpServer;

class ApiConfig {
public:
    ApiConfig(IEspHttpServer& espHttpServer);
    ~ApiConfig();

    esp_err_t get_config_handler(httpd_req_t *req);
    esp_err_t put_config_handler(httpd_req_t *req);
    esp_err_t set_circular_navigation_handler(httpd_req_t *req);

private:
    IEspHttpServer& espHttpServer_;
};
