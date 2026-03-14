#include "ApiPresetValues.hpp"
#include "IEspHttpServer.hpp"

ApiPresetValues::ApiPresetValues(IEspHttpServer& espHttpServer) : espHttpServer_(espHttpServer) {}
ApiPresetValues::~ApiPresetValues() = default;

esp_err_t ApiPresetValues::get_preset_values_handler(httpd_req_t *req) {
    const char *resp = "[0, 128, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiPresetValues::set_preset_value_handler(httpd_req_t *req) {
    const char *resp = "{\"index\": 45, \"value\": 128}";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}
