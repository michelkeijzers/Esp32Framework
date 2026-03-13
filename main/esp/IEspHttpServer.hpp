#pragma once
#include <string>
#include <functional>
#include "../esp/esp_error_if.hpp"
#include "../esp/esp_http_server_if.hpp"

// Interface for ESP32 HTTP server abstraction
class IEspHttpServer {
public:
    virtual ~IEspHttpServer() = default;

    virtual esp_err_t httpd_resp_set_type(httpd_req_t *req, const char *type) = 0;
    virtual esp_err_t httpd_resp_send(httpd_req_t *req, const char *buf, size_t len) = 0;
};
