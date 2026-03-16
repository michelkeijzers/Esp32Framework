#pragma once
#include "../../../main/nodes/webserver/http_task/apis/IApiLogging.hpp"
#include <vector>
#include <string>

class MockApiLogging : public IApiLogging {
public:
    MockApiLogging() = default;
    ~MockApiLogging() override = default;

    esp_err_t logging_handler(httpd_req_t *req) override {
        called_methods.push_back("logging_handler");
        return ESP_OK;
    }

    std::vector<std::string> called_methods;
    void clear() { called_methods.clear(); }
};
