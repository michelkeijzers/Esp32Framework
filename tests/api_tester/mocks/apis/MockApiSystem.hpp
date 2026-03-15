#pragma once
#include "../../../main/slaves/webserver_slave/common/apis/IApiSystem.hpp"
#include <vector>
#include <string>

class MockApiSystem : public IApiSystem {
public:
    MockApiSystem() = default;
    ~MockApiSystem() override = default;

    esp_err_t reboot_handler(httpd_req_t *req) override {
        called_methods.push_back("reboot_handler");
        return ESP_OK;
    }

    esp_err_t factory_reset_handler(httpd_req_t *req) override {
        called_methods.push_back("factory_reset_handler");
        return ESP_OK;
    }

    std::vector<std::string> called_methods;
    void clear() { called_methods.clear(); }
};
