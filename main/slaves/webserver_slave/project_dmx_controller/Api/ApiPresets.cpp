
#include "ApiPresets.hpp"
#include "IEspHttpServer.hpp"

ApiPresets::ApiPresets(IEspHttpServer& espHttpServer) : espHttpServer_(espHttpServer) {}
ApiPresets::~ApiPresets() = default;

esp_err_t ApiPresets::get_presets_handler(httpd_req_t *req) {
    const char *resp = "[{\"name\":\"Warm White\",\"active\":true},{\"name\":\"Cool Blue\",\"active\":false}]";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiPresets::save_preset_handler(httpd_req_t *req) {
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, "{\"ack\":\"ok\"}", HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiPresets::get_active_preset_numbers_handler(httpd_req_t *req) {
    const char *resp = "[1, 2, 5, 7]";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiPresets::select_preset_handler(httpd_req_t *req) {
    const char *resp = "{\"preset_name\":\"Warm White\"}";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiPresets::blackout_handler(httpd_req_t *req) {
    const char *resp = "{\"preset_name\":\"Blackout\"}";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiPresets::move_preset_up_handler(httpd_req_t *req) {
    const char *resp = "[{\"name\":\"Cool Blue\",\"active\":false},{\"name\":\"Warm White\",\"active\":true}]";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiPresets::move_preset_down_handler(httpd_req_t *req) {
    const char *resp = "[{\"name\":\"Cool Blue\",\"active\":false},{\"name\":\"Warm White\",\"active\":true}]";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiPresets::delete_preset_handler(httpd_req_t *req) {
    const char *resp = "[{\"name\":\"Warm White\",\"active\":true}]";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiPresets::insert_preset_at_handler(httpd_req_t *req) {
    const char *resp = "[{\"name\":\"\",\"active\":false},{\"name\":\"Warm White\",\"active\":true},{\"name\":\"Cool Blue\",\"active\":false}]";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiPresets::swap_preset_activation_handler(httpd_req_t *req) {
    const char *resp = "[{\"name\":\"Warm White\",\"active\":false},{\"name\":\"Cool Blue\",\"active\":true}]";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}
