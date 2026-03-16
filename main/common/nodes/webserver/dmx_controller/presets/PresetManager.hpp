#pragma once

#include "IPresetManager.hpp"
#include "../../esp/esp_nvs/IEspNvs.hpp"
#include <vector>
#include <memory>

class PresetManager : public IPresetManager {
public:
    explicit PresetManager(IEspNvs& nvs);
    ~PresetManager() override = default;

    esp_err_t load_presets() override;
    std::vector<Preset> get_presets() const override;
    const Preset* get_preset(uint32_t number) const override;
    std::vector<uint32_t> get_active_presets() const override;
    esp_err_t save_preset(const Preset& preset) override;
    esp_err_t delete_preset(uint32_t number) override;
    esp_err_t select_preset(uint32_t number) override;
    esp_err_t move_preset(uint32_t number, bool up) override;
    esp_err_t swap_activation(uint32_t number) override;
    esp_err_t blackout() override;
    esp_err_t commit() override;
    esp_err_t reset() override;

private:
    IEspNvs& nvs_;
    std::vector<Preset> presets_;
    
    static constexpr const char* NAMESPACE_NAME = "presets";
    static constexpr const char* PRESET_COUNT_KEY = "count";
    static constexpr size_t MAX_PRESET_NAME_LEN = 63;
    static constexpr uint32_t DMX_VALUES_SIZE = 512;
    
    // Helper to get NVS key names for preset data
    static std::string get_preset_name_key(uint32_t preset_num);
    static std::string get_preset_data_key(uint32_t preset_num);
    static std::string get_preset_active_key(uint32_t preset_num);
    static std::string get_preset_universe_key(uint32_t preset_num);
};
