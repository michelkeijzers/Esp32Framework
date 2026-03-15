#pragma once
#include "../../../../common/esp_http_server/esp_http_server_if.hpp"
#include "../../../../common/esp/esp_error_if.hpp"

class IEspHttpServer;

class ApiNodes {
public:
    ApiNodes(IEspHttpServer& espHttpServer);
    ~ApiNodes();

    esp_err_t get_nodes_info_handler(httpd_req_t *req);
    esp_err_t save_nodes_info_handler(httpd_req_t *req);

private:
    IEspHttpServer& espHttpServer_;
};
