
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
    printf("Saving preset...\n");
    
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, "{\"ack\":\"ok\"}", HTTPD_RESP_USE_STRLEN);
    return 0;
}
