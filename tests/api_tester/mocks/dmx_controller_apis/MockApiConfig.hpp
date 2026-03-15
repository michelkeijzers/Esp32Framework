#pragma once
#include "../../../main/slaves/webserver_slave/dmx_controller/apis/IApiConfig.hpp"
#include <vector>
#include <string>

class MockApiConfig : public IApiConfig {
public:
    MockApiConfig() = default;
    ~MockApiConfig() override = default;

    esp_err_t get_config_handler(httpd_req_t *req) override {
        called_methods.push_back("get_config_handler");
        return ESP_OK;
    }

    esp_err_t put_config_handler(httpd_req_t *req) override {
        called_methods.push_back("put_config_handler");
        return ESP_OK;
    }

    esp_err_t set_circular_navigation_handler(httpd_req_t *req) override {
        called_methods.push_back("set_circular_navigation_handler");
        return ESP_OK;
    }

    std::vector<std::string> called_methods;
    void clear() { called_methods.clear(); }
};
