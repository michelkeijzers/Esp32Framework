#pragma once

#include "common/esp/esp_nvs/IEspNvs.hpp"
#include "common/esp/esp_logger/IEspLogger.hpp"
#include "projects/dmx_controller/presets_task/PresetManager.hpp"

/**
 * @brief Context for PresetsTask
 * Contains all dependencies needed by PresetsTask
 */
class PresetsTaskContext
{
  public:
    // ESP Services
    IEspLogger *logger;
    IEspNvs *nvs;

    // Managers
    IPresetManager *presetManager;

    PresetsTaskContext(IEspLogger *logger, IEspNvs *nvs, IPresetManager *presetManager)
        : logger(logger), nvs(nvs), presetManager(presetManager)
    {
    }
};
