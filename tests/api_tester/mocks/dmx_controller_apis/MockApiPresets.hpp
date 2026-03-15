#pragma once
#include "../../../main/slaves/webserver_slave/dmx_controller/apis/IApiPresets.hpp"
#include <vector>
#include <string>

class MockApiPresets : public IApiPresets {
public:
    MockApiPresets() = default;
    ~MockApiPresets() override = default;

    esp_err_t get_presets_handler(httpd_req_t *req) override {
        called_methods.push_back("get_presets_handler");
        return ESP_OK;
    }

    esp_err_t save_preset_handler(httpd_req_t *req) override {
        called_methods.push_back("save_preset_handler");
        return ESP_OK;
    }

    esp_err_t get_active_preset_numbers_handler(httpd_req_t *req) override {
        called_methods.push_back("get_active_preset_numbers_handler");
        return ESP_OK;
    }

    esp_err_t select_preset_handler(httpd_req_t *req) override {
        called_methods.push_back("select_preset_handler");
        return ESP_OK;
    }

    esp_err_t blackout_handler(httpd_req_t *req) override {
        called_methods.push_back("blackout_handler");
        return ESP_OK;
    }

    esp_err_t move_preset_up_handler(httpd_req_t *req) override {
        called_methods.push_back("move_preset_up_handler");
        return ESP_OK;
    }

    esp_err_t move_preset_down_handler(httpd_req_t *req) override {
        called_methods.push_back("move_preset_down_handler");
        return ESP_OK;
    }

    esp_err_t delete_preset_handler(httpd_req_t *req) override {
        called_methods.push_back("delete_preset_handler");
        return ESP_OK;
    }

    esp_err_t insert_preset_at_handler(httpd_req_t *req) override {
        called_methods.push_back("insert_preset_at_handler");
        return ESP_OK;
    }

    esp_err_t swap_preset_activation_handler(httpd_req_t *req) override {
        called_methods.push_back("swap_preset_activation_handler");
        return ESP_OK;
    }

    std::vector<std::string> called_methods;
    void clear() { called_methods.clear(); }
};
