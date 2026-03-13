
#pragma once
#include "../../../esp/esp_http_server_if.hpp"
#include "../../../esp/esp_error_if.hpp"

class ApiStatus {
public:
    static esp_err_t get_status_handler(httpd_req_t *req);
};
