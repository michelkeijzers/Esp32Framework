#pragma once

#include "common/esp/esp_logger/IEspLogger.hpp"
#include "projects/dmx_controller/service_locator/HttpTaskContext.hpp"
#include "projects/dmx_controller/service_locator/PresetsTaskContext.hpp"

/**
 * @brief Context for DmxControllerTask
 * Contains all dependencies needed by DmxControllerTask and references to sub-contexts for subsystem tasks
 */
class DmxControllerTaskContext
{
  public:
    // ESP Services
    IEspLogger *logger;

    // Sub-contexts for subsystem tasks
    HttpTaskContext *httpTaskContext;
    PresetsTaskContext *presetsTaskContext;
    // EspNowTaskContext can be added when needed

    DmxControllerTaskContext(IEspLogger *logger, HttpTaskContext *httpTaskContext,
                             PresetsTaskContext *presetsTaskContext)
        : logger(logger), httpTaskContext(httpTaskContext), presetsTaskContext(presetsTaskContext)
    {
    }
};
