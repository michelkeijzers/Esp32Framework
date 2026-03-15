#pragma once

#include "../../../../main/slaves/webserver_slave/dmx_controller/presets/IPresetManager.hpp"
#include <vector>
#include <memory>
#include <algorithm>

class MockPresetManager : public IPresetManager {
public:
    MockPresetManager() = default;
    ~MockPresetManager() override = default;

    esp_err_t load_presets() override { return ESP_OK; }
    std::vector<Preset> get_presets() const override { return presets_; }
    const Preset* get_preset(uint32_t number) const override {
        for (const auto& preset : presets_) {
            if (preset.number == number) {
                return &preset;
            }
        }
        return nullptr;
    }
    
    std::vector<uint32_t> get_active_presets() const override {
        std::vector<uint32_t> active;
        for (const auto& preset : presets_) {
            if (preset.active) {
                active.push_back(preset.number);
            }
        }
        return active;
    }

    esp_err_t save_preset(const Preset& preset) override {
        auto it = std::find_if(presets_.begin(), presets_.end(),
                               [preset](const Preset& p) { return p.number == preset.number; });
        if (it != presets_.end()) {
            *it = preset;
        } else {
            presets_.push_back(preset);
            std::sort(presets_.begin(), presets_.end(),
                      [](const Preset& a, const Preset& b) { return a.number < b.number; });
        }
        return ESP_OK;
    }

    esp_err_t delete_preset(uint32_t number) override {
        auto it = std::find_if(presets_.begin(), presets_.end(),
                               [number](const Preset& p) { return p.number == number; });
        if (it != presets_.end()) {
            presets_.erase(it);
            return ESP_OK;
        }
        return ESP_ERR_NOT_FOUND;
    }

    esp_err_t select_preset(uint32_t number) override {
        auto it = std::find_if(presets_.begin(), presets_.end(),
                               [number](const Preset& p) { return p.number == number; });
        if (it == presets_.end()) {
            return ESP_ERR_NOT_FOUND;
        }
        for (auto& preset : presets_) {
            preset.active = (preset.number == number);
        }
        return ESP_OK;
    }

    esp_err_t move_preset(uint32_t number, bool up) override {
        auto it = std::find_if(presets_.begin(), presets_.end(),
                               [number](const Preset& p) { return p.number == number; });
        if (it == presets_.end()) {
            return ESP_ERR_NOT_FOUND;
        }
        if (up && it == presets_.begin()) {
            return ESP_ERR_INVALID_STATE;
        }
        if (!up && it == (presets_.end() - 1)) {
            return ESP_ERR_INVALID_STATE;
        }
        if (up) {
            std::swap(*it, *(it - 1));
        } else {
            std::swap(*it, *(it + 1));
        }
        return ESP_OK;
    }

    esp_err_t swap_activation(uint32_t number) override {
        auto it = std::find_if(presets_.begin(), presets_.end(),
                               [number](const Preset& p) { return p.number == number; });
        if (it == presets_.end()) {
            return ESP_ERR_NOT_FOUND;
        }
        it->active = !it->active;
        return ESP_OK;
    }

    esp_err_t blackout() override {
        for (auto& preset : presets_) {
            preset.active = false;
        }
        return ESP_OK;
    }

    esp_err_t commit() override { return ESP_OK; }
    esp_err_t reset() override {
        presets_.clear();
        return ESP_OK;
    }

private:
    std::vector<Preset> presets_;
};
