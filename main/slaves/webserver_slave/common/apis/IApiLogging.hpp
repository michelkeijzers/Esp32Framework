#pragma once
#include "../../../../common/esp/esp_http_server/esp_http_server_if.hpp"
#include "../../../../common/esp/esp_error/esp_error_if.hpp"

class IApiLogging {
public:
    virtual ~IApiLogging() = default;

    virtual esp_err_t logging_handler(httpd_req_t *req) = 0;
};
