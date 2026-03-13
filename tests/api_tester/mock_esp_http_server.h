#pragma once
#include <string>
#include <cstring>

#include "../../main/esp/esp_error_if.hpp"
#include "../../main/esp/esp_http_server_if.hpp"


#define HTTPD_RESP_USE_STRLEN -1
#ifndef ESP_OK
#define ESP_OK 0
#endif



inline esp_err_t httpd_resp_set_type(httpd_req_t *req, const char *type) {
    req->content_type = type;
    return 0;
}

inline esp_err_t httpd_resp_send(httpd_req_t *req, const char *buf, size_t len) {
    if (len == HTTPD_RESP_USE_STRLEN) {
        req->response = std::string(buf);
    } else {
        req->response = std::string(buf, len);
    }
    return 0;
}
