#pragma once
#include "../../../../common/esp_http_server/esp_http_server_if.hpp"
#include "../../../../common/esp/esp_error_if.hpp"
#include "../presets/IPresetManager.hpp"

class IEspHttpServer;

class ApiPresetValues {
public:
    ApiPresetValues(IEspHttpServer& espHttpServer, IPresetManager& presetManager);
    ~ApiPresetValues();

    esp_err_t get_preset_values_handler(httpd_req_t *req);
    esp_err_t set_preset_value_handler(httpd_req_t *req);

private:
    IEspHttpServer& espHttpServer_;
    IPresetManager& presetManager_;
};
