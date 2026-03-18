#include "RtosTask.hpp"

RtosTask::RtosTask(const char *name, uint32_t stackSize, UBaseType_t priority)
    : name_(name), stackSize_(stackSize), priority_(priority)
{
}

esp_err_t RtosTask::init()
{
    // Base initialization logic for RTOS tasks can be added here if needed
    return ESP_OK;
}

esp_err_t RtosTask::start()
{
    // Base logic to start the RTOS task can be added here if needed
    return ESP_OK;
}
