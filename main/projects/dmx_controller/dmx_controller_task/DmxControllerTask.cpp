#include "DmxControllerTask.hpp"
#include "../service_locator/DmxServiceLocator.hpp"
#include "../http_task/DmxControllerHttpTask.hpp"
#include "../../../common/tasks/RtosTask.hpp"

DmxControllerTask::DmxControllerTask(DmxServiceLocator &serviceLocator, const char *name, uint32_t stackSize,
                                     UBaseType_t priority)
    : RtosTask(name, stackSize, priority), _serviceLocator(serviceLocator)
{
}

esp_err_t DmxControllerTask::init()
{
    esp_err_t err = ESP_OK;

    // // Create Http Task.
    // auto httpTaskContext = _serviceLocator.createHttpTaskContext();
    // auto httpTask = new DmxControllerHttpTask(*httpTaskContext, "HttpTask", 4096, 5);
    // err = httpTask->init();
    // if (err != ESP_OK)
    // {
    //     // Handle initialization error (e.g., log it
    // }

    // // Create Presets task.
    // auto presetsTaskContext = _serviceLocator.createPresetsTaskContext();
    // auto presetsTask = new PresetsTask(*presetsTaskContext, "PresetsTask", 4096, 5);
    // err = presetsTask->init();
    // if (err != ESP_OK)
    // {
    //     // Handle initialization error (e.g., log it)
    // }

    return ESP_OK;
}

esp_err_t DmxControllerTask::start()
{
    // Start the subsystem tasks here
    // For example:
    // httpTask->start();

    return ESP_OK;
}
