#pragma once
#include "../../../main/common/nodes/webserver/http_task/apis/IApiPresetValues.hpp"
#include <vector>
#include <string>

class MockApiPresetValues : public IApiPresetValues {
public:
    MockApiPresetValues() = default;
    ~MockApiPresetValues() override = default;

    esp_err_t get_preset_values_handler(httpd_req_t *req) override {
        called_methods.push_back("get_preset_values_handler");
        return ESP_OK;
    }

    esp_err_t set_preset_value_handler(httpd_req_t *req) override {
        called_methods.push_back("set_preset_value_handler");
        return ESP_OK;
    }

    std::vector<std::string> called_methods;
    void clear() { called_methods.clear(); }
};
