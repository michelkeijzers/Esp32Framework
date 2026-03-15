#include "PresetManager.hpp"
#include <algorithm>
#include <cstring>

PresetManager::PresetManager(IEspNvs& nvs) : nvs_(nvs) {}

std::string PresetManager::get_preset_name_key(uint32_t preset_num) {
    return "preset_" + std::to_string(preset_num) + "_name";
}

std::string PresetManager::get_preset_data_key(uint32_t preset_num) {
    return "preset_" + std::to_string(preset_num) + "_data";
}

std::string PresetManager::get_preset_active_key(uint32_t preset_num) {
    return "preset_" + std::to_string(preset_num) + "_active";
}

std::string PresetManager::get_preset_universe_key(uint32_t preset_num) {
    return "preset_" + std::to_string(preset_num) + "_universe";
}

esp_err_t PresetManager::load_presets() {
    presets_.clear();
    
    // Open NVS namespace
    nvs_handle_t handle;
    esp_err_t err = nvs_.nvs_open(NAMESPACE_NAME, NVS_READONLY, &handle);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) {
        return err;
    }
    
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        // Namespace doesn't exist yet
        return ESP_OK;
    }

    // Read preset count
    uint32_t preset_count = 0;
    err = nvs_.nvs_get_u32(handle, PRESET_COUNT_KEY, &preset_count);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) {
        nvs_.nvs_close(handle);
        return err;
    }

    // Load each preset
    for (uint32_t i = 0; i < preset_count; ++i) {
        Preset preset(i);

        // Load name
        char name_buf[MAX_PRESET_NAME_LEN + 1] = {0};
        size_t name_len = sizeof(name_buf);
        err = nvs_.nvs_get_str(handle, get_preset_name_key(i).c_str(), name_buf, &name_len);
        if (err == ESP_OK) {
            preset.name = name_buf;
        }

        // Load DMX values
        size_t data_len = DMX_VALUES_SIZE;
        err = nvs_.nvs_get_blob(handle, get_preset_data_key(i).c_str(), 
                                preset.dmx_values.data(), &data_len);
        if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) {
            nvs_.nvs_close(handle);
            return err;
        }

        // Load active flag
        uint8_t active = 0;
        err = nvs_.nvs_get_u32(handle, get_preset_active_key(i).c_str(), 
                               reinterpret_cast<uint32_t*>(&active));
        if (err == ESP_OK) {
            preset.active = (active != 0);
        }

        // Load universe
        uint32_t universe = 0;
        err = nvs_.nvs_get_u32(handle, get_preset_universe_key(i).c_str(), &universe);
        if (err == ESP_OK) {
            preset.universe = static_cast<uint8_t>(universe);
        }

        presets_.push_back(preset);
    }

    nvs_.nvs_close(handle);
    return ESP_OK;
}

std::vector<Preset> PresetManager::get_presets() const {
    return presets_;
}

const Preset* PresetManager::get_preset(uint32_t number) const {
    for (const auto& preset : presets_) {
        if (preset.number == number) {
            return &preset;
        }
    }
    return nullptr;
}

std::vector<uint32_t> PresetManager::get_active_presets() const {
    std::vector<uint32_t> active;
    for (const auto& preset : presets_) {
        if (preset.active) {
            active.push_back(preset.number);
        }
    }
    return active;
}

esp_err_t PresetManager::save_preset(const Preset& preset) {
    // Check if preset with this number already exists
    auto it = std::find_if(presets_.begin(), presets_.end(),
                           [preset](const Preset& p) { return p.number == preset.number; });
    
    if (it != presets_.end()) {
        *it = preset;
    } else {
        presets_.push_back(preset);
        // Sort by number to maintain order
        std::sort(presets_.begin(), presets_.end(),
                  [](const Preset& a, const Preset& b) { return a.number < b.number; });
    }
    
    return ESP_OK;
}

esp_err_t PresetManager::delete_preset(uint32_t number) {
    auto it = std::find_if(presets_.begin(), presets_.end(),
                           [number](const Preset& p) { return p.number == number; });
    
    if (it != presets_.end()) {
        presets_.erase(it);
        return ESP_OK;
    }
    
    return ESP_ERR_NOT_FOUND;
}

esp_err_t PresetManager::select_preset(uint32_t number) {
    // Check if preset exists
    auto it = std::find_if(presets_.begin(), presets_.end(),
                           [number](const Preset& p) { return p.number == number; });
    if (it == presets_.end()) {
        return ESP_ERR_NOT_FOUND;
    }

    // Deactivate all, activate selected
    for (auto& preset : presets_) {
        preset.active = (preset.number == number);
    }
    
    return ESP_OK;
}

esp_err_t PresetManager::move_preset(uint32_t number, bool up) {
    auto it = std::find_if(presets_.begin(), presets_.end(),
                           [number](const Preset& p) { return p.number == number; });
    
    if (it == presets_.end()) {
        return ESP_ERR_NOT_FOUND;
    }

    if (up && it == presets_.begin()) {
        return ESP_ERR_INVALID_STATE;  // Already at top
    }
    if (!up && it == (presets_.end() - 1)) {
        return ESP_ERR_INVALID_STATE;  // Already at bottom
    }

    if (up) {
        std::swap(*it, *(it - 1));
    } else {
        std::swap(*it, *(it + 1));
    }
    
    return ESP_OK;
}

esp_err_t PresetManager::swap_activation(uint32_t number) {
    auto it = std::find_if(presets_.begin(), presets_.end(),
                           [number](const Preset& p) { return p.number == number; });
    
    if (it == presets_.end()) {
        return ESP_ERR_NOT_FOUND;
    }

    it->active = !it->active;
    return ESP_OK;
}

esp_err_t PresetManager::blackout() {
    for (auto& preset : presets_) {
        preset.active = false;
    }
    return ESP_OK;
}

esp_err_t PresetManager::commit() {
    // Open NVS namespace for writing
    nvs_handle_t handle;
    esp_err_t err = nvs_.nvs_open(NAMESPACE_NAME, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        return err;
    }

    // Write preset count
    err = nvs_.nvs_set_u32(handle, PRESET_COUNT_KEY, static_cast<uint32_t>(presets_.size()));
    if (err != ESP_OK) {
        nvs_.nvs_close(handle);
        return err;
    }

    // Write each preset
    for (const auto& preset : presets_) {
        // Write name
        err = nvs_.nvs_set_str(handle, get_preset_name_key(preset.number).c_str(), 
                               preset.name.c_str());
        if (err != ESP_OK) {
            nvs_.nvs_close(handle);
            return err;
        }

        // Write DMX values
        err = nvs_.nvs_set_blob(handle, get_preset_data_key(preset.number).c_str(),
                                preset.dmx_values.data(), DMX_VALUES_SIZE);
        if (err != ESP_OK) {
            nvs_.nvs_close(handle);
            return err;
        }

        // Write active flag
        err = nvs_.nvs_set_u32(handle, get_preset_active_key(preset.number).c_str(),
                               preset.active ? 1 : 0);
        if (err != ESP_OK) {
            nvs_.nvs_close(handle);
            return err;
        }

        // Write universe
        err = nvs_.nvs_set_u32(handle, get_preset_universe_key(preset.number).c_str(),
                               preset.universe);
        if (err != ESP_OK) {
            nvs_.nvs_close(handle);
            return err;
        }
    }

    // Commit the transaction
    err = nvs_.nvs_commit(handle);
    nvs_.nvs_close(handle);
    
    return err;
}

esp_err_t PresetManager::reset() {
    presets_.clear();
    return load_presets();
}
