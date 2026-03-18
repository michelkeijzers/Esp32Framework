#include "DmxControllerTask.hpp"

#include "DmxControllerTask.hpp"

DmxControllerTask::DmxControllerTask(DmxServiceLocator &locator) : IDmxControllerTask(), serviceLocator_(locator) {}

esp_err_t DmxControllerTask::init()
{
    // Initialize any resources needed by the controller task here
    // For example, create and initialize subsystem tasks (HttpTask, PresetsTask, EspNowTask)
    // using the service locator to get their dependencies

    // Example (pseudocode):
    // httpTask = new DmxControllerHttpTask(serviceLocator.createHttpTaskContext());
    // httpTask->init();

    return ESP_OK;
}

esp_err_t DmxControllerTask::start()
{
    // Start the subsystem tasks here
    // For example:
    // httpTask->start();

    return ESP_OK;
}
