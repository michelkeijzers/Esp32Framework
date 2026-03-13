#include "EspHttpServer.hpp"
#include "esp_http_server_types.hpp"


EspHttpServer::EspHttpServer() {}
EspHttpServer::~EspHttpServer() {}

esp_err_t EspHttpServer::httpd_resp_set_type(httpd_req_t *req, const char *type) {
    // Implement the method for ESP32
    return httpd_resp_set_type(req, type);
}

esp_err_t EspHttpServer::httpd_resp_send(httpd_req_t *req, const char *buf, size_t len) {
    // Implement the method for ESP32
    return httpd_resp_send(req, buf, len);
}