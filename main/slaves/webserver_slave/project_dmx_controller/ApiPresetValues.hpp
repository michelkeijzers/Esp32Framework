#pragma once
#include "../../../esp/esp_http_server_if.hpp"
#include "../../../esp/esp_error_if.hpp"

class IEspHttpServer;

class ApiPresetValues {
public:
    ApiPresetValues(IEspHttpServer& espHttpServer);
    ~ApiPresetValues();

    esp_err_t get_preset_values_handler(httpd_req_t *req);
    esp_err_t set_preset_value_handler(httpd_req_t *req);

private:
    IEspHttpServer& espHttpServer_;
};
