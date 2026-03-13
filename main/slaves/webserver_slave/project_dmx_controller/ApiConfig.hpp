
#pragma once
#include "../../../esp/esp_http_server_if.hpp"
#include "../../../esp/esp_error_if.hpp"


class ApiConfig {
public:
    static esp_err_t get_config_handler(httpd_req_t *req);
    static esp_err_t put_config_handler(httpd_req_t *req);
};
