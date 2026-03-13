
#pragma once
#include "esp_http_server_if.hpp"
#include "../../../esp/esp_error_if.hpp"

class ApiPresets {
public:
    static esp_err_t get_presets_handler(httpd_req_t *req);
    static esp_err_t save_preset_handler(httpd_req_t *req);
};
