#pragma once

#include <vector>
#include <cstdint>
#include "Preset.hpp"
#include "../esp/esp_error_if.hpp"

class IPresetManager {
public:
    virtual ~IPresetManager() = default;

    /**
     * Load all presets from persistent storage into memory.
     * Call once during startup.
     */
    virtual esp_err_t load_presets() = 0;

    /**
     * Get all presets currently in memory.
     */
    virtual std::vector<Preset> get_presets() const = 0;

    /**
     * Get a specific preset by index.
     */
    virtual const Preset* get_preset(uint32_t number) const = 0;

    /**
     * Get indices of all active presets.
     */
    virtual std::vector<uint32_t> get_active_presets() const = 0;

    /**
     * Save or update a preset in memory.
     * Does NOT persist to storage until commit() is called.
     */
    virtual esp_err_t save_preset(const Preset& preset) = 0;

    /**
     * Delete a preset from memory.
     * Does NOT persist to storage until commit() is called.
     */
    virtual esp_err_t delete_preset(uint32_t number) = 0;

    /**
     * Select (activate) a single preset, deactivate all others.
     * Does NOT persist to storage until commit() is called.
     */
    virtual esp_err_t select_preset(uint32_t number) = 0;

    /**
     * Move a preset up or down in the list.
     * Does NOT persist to storage until commit() is called.
     */
    virtual esp_err_t move_preset(uint32_t number, bool up) = 0;

    /**
     * Toggle activation status of a preset.
     * Does NOT persist to storage until commit() is called.
     */
    virtual esp_err_t swap_activation(uint32_t number) = 0;

    /**
     * Deactivate all presets (blackout).
     * Does NOT persist to storage until commit() is called.
     */
    virtual esp_err_t blackout() = 0;

    /**
     * Persist all in-memory presets to permanent storage (NVS).
     */
    virtual esp_err_t commit() = 0;

    /**
     * Clear memory cache and reload from storage.
     */
    virtual esp_err_t reset() = 0;
};
