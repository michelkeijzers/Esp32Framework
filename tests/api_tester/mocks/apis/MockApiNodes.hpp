#pragma once
#include "../../../main/common/nodes/webserver/http_task/apis/IApiNodes.hpp"
#include <vector>
#include <string>

class MockApiNodes : public IApiNodes {
public:
    MockApiNodes() = default;
    ~MockApiNodes() override = default;

    esp_err_t get_nodes_info_handler(httpd_req_t *req) override {
        called_methods.push_back("get_nodes_info_handler");
        return ESP_OK;
    }

    esp_err_t save_nodes_info_handler(httpd_req_t *req) override {
        called_methods.push_back("save_nodes_info_handler");
        return ESP_OK;
    }

    std::vector<std::string> called_methods;
    void clear() { called_methods.clear(); }
};
