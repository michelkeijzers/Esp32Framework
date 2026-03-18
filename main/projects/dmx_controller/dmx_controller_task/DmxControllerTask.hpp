#pragma once

#include "../service_locator/DmxServiceLocator.hpp"
#include "IDmxControllerTask.hpp"

/**
 * @brief Main DMX Controller Task
 * Orchestrates creation and management of subsystem tasks:
 * - HttpTask (web server and REST APIs)
 * - PresetsTask (preset management)
 * - EspNowTask (wireless communication with other nodes)
 */
class DmxControllerTask : IDmxControllerTask
{
  public:
    DmxControllerTask(DmxServiceLocator &locator);

    esp_err_t init() override;
    esp_err_t start();

  private:
    DmxServiceLocator &serviceLocator_;
};
