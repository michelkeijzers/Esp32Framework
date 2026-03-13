
#include "ApiConfig.hpp"
#include "IEspHttpServer.hpp"

ApiConfig::ApiConfig(IEspHttpServer& espHttpServer) : espHttpServer_(espHttpServer) {}
ApiConfig::~ApiConfig() = default;

esp_err_t ApiConfig::get_config_handler(httpd_req_t *req) {
    const char *resp = "{\"config\":true}";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiConfig::put_config_handler(httpd_req_t *req) {
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, "{\"ack\":\"ok\"}", HTTPD_RESP_USE_STRLEN);
    return 0;
}

esp_err_t ApiConfig::set_circular_navigation_handler(httpd_req_t *req) {
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, "{\"ack\":\"ok\"}", HTTPD_RESP_USE_STRLEN);
    return 0;
}
