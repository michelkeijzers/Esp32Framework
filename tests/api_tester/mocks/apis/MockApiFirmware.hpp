#pragma once
#include "../../../main/slaves/webserver_slave/common/apis/IApiFirmware.hpp"
#include <vector>
#include <string>

class MockApiFirmware : public IApiFirmware {
public:
    MockApiFirmware() = default;
    ~MockApiFirmware() override = default;

    esp_err_t firmware_chunk_handler(httpd_req_t *req) override {
        called_methods.push_back("firmware_chunk_handler");
        return ESP_OK;
    }

    esp_err_t firmware_finish_handler(httpd_req_t *req) override {
        called_methods.push_back("firmware_finish_handler");
        return ESP_OK;
    }

    std::vector<std::string> called_methods;
    void clear() { called_methods.clear(); }
};
