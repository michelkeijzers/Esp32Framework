#pragma once

#include "IDmxControllerTask.hpp"
#include "../../../common/tasks/RtosTask.hpp"

class DmxServiceLocator;
/**
 * @brief Main DMX Controller Task
 * Orchestrates creation and management of subsystem tasks:
 * - HttpTask (web server and REST APIs)
 * - PresetsTask (preset management)
 * - EspNowTask (wireless communication with other nodes)
 */
class DmxControllerTask : public RtosTask, IDmxControllerTask
{
  public:
    DmxControllerTask(DmxServiceLocator &locator, const char *name, uint32_t stackSize, UBaseType_t priority);

    esp_err_t init() override;
    esp_err_t start() override;

  private:
    DmxServiceLocator &_serviceLocator;
};
