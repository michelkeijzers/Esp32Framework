
#include "ApiStatus.hpp"
#include "IEspHttpServer.hpp"

ApiStatus::ApiStatus(IEspHttpServer& espHttpServer) : espHttpServer_(espHttpServer) {}
ApiStatus::~ApiStatus() = default;

esp_err_t ApiStatus::get_status_handler(httpd_req_t *req) {
    const char *resp = "[{\"name\":\"Master\",\"role\":\"Master\",\"slave_type\":\"Webserver\",\"status_watchdog\":\"OK\"}]";
    espHttpServer_.httpd_resp_set_type(req, "application/json");
    espHttpServer_.httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return 0;
}
