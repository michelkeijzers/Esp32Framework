#pragma once
#include "../../../../common/esp_http_server/esp_http_server_if.hpp"
#include "../../../../common/esp/esp_error_if.hpp"

class IEspHttpServer;

class ApiFirmware {
public:
    ApiFirmware(IEspHttpServer& espHttpServer);
    ~ApiFirmware();

    esp_err_t firmware_chunk_handler(httpd_req_t *req);
    esp_err_t firmware_finish_handler(httpd_req_t *req);

private:
    IEspHttpServer& espHttpServer_;
};
