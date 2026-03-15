
#pragma once
#include "IApiStatus.hpp"
#include "../../../../common/esp_http_server/esp_http_server_if.hpp"
#include "../../../../common/esp/esp_error_if.hpp"

class IEspHttpServer;

class ApiStatus : public IApiStatus {
public:
    ApiStatus(IEspHttpServer& espHttpServer);
    ~ApiStatus();

    esp_err_t get_status_handler(httpd_req_t *req) override;
    esp_err_t get_status_stream_handler(httpd_req_t *req) override;

private:
    IEspHttpServer& espHttpServer_;
};
