#pragma once

#include "../service_locator/DmxServiceLocator.hpp"

/**
 * @brief Main DMX Controller Task
 * Orchestrates creation and management of subsystem tasks:
 * - HttpTask (web server and REST APIs)
 * - PresetsTask (preset management)
 * - EspNowTask (wireless communication with other nodes)
 */
class DmxControllerTask
{
  private:
    DmxServiceLocator &serviceLocator;

  public:
    DmxControllerTask(DmxServiceLocator &locator) : serviceLocator(locator) {}

    esp_err_t init();
    esp_err_t start();
};
