#pragma once
#include "IEspHttpServer.hpp"
#include <string>
#include <functional>

// Real implementation for ESP32 HTTP server
class EspHttpServer : public IEspHttpServer {
public:
    EspHttpServer();
    ~EspHttpServer() override;

    esp_err_t httpd_resp_set_type(httpd_req_t *req, const char *type) override;
    esp_err_t httpd_resp_send(httpd_req_t *req, const char *buf, size_t len) override;

    // Add any ESP-IDF specific methods as needed
};
