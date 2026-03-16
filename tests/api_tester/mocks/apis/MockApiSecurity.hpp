#pragma once
#include "../../../main/common/nodes/webserver/http_task/apis/IApiSecurity.hpp"
#include <vector>
#include <string>

class MockApiSecurity : public IApiSecurity {
public:
    MockApiSecurity() = default;
    ~MockApiSecurity() override = default;

    esp_err_t esp_now_key_handler(httpd_req_t *req) override {
        called_methods.push_back("esp_now_key_handler");
        return ESP_OK;
    }

    esp_err_t wifi_password_handler(httpd_req_t *req) override {
        called_methods.push_back("wifi_password_handler");
        return ESP_OK;
    }

    std::vector<std::string> called_methods;
    void clear() { called_methods.clear(); }
};
