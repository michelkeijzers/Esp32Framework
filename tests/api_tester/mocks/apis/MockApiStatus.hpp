#pragma once
#include "../../../main/common/nodes/webserver/http_task/apis/IApiStatus.hpp"
#include <vector>
#include <string>

class MockApiStatus : public IApiStatus {
public:
    MockApiStatus() = default;
    ~MockApiStatus() override = default;

    esp_err_t get_status_handler(httpd_req_t *req) override {
        called_methods.push_back("get_status_handler");
        return ESP_OK;
    }

    esp_err_t get_status_stream_handler(httpd_req_t *req) override {
        called_methods.push_back("get_status_stream_handler");
        return ESP_OK;
    }

    std::vector<std::string> called_methods;
    void clear() { called_methods.clear(); }
};
