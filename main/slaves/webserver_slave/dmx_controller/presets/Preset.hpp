#pragma once

#include <cstdint>
#include <string>
#include <array>

struct Preset {
    uint32_t number;                            // Preset index (0-based)
    std::string name;                           // Preset name (max 63 chars for NVS)
    std::array<uint8_t, 512> dmx_values{};      // 512 DMX channel values (0-255 each)
    bool active;                                // Whether preset is active
    uint8_t universe;                           // Universe number (optional, for extended functionality)

    Preset(uint32_t num = 0, const std::string& preset_name = "", bool is_active = false, uint8_t univ = 0)
        : number(num), name(preset_name), active(is_active), universe(univ) {
        dmx_values.fill(0);
    }
};
