#pragma once

class DmxServiceLocator;

class IDmxControllerTask
{
  public:
    IDmxControllerTask() = default;
    virtual ~IDmxControllerTask() = default;

    virtual esp_err_t init() = 0;
    virtual esp_err_t start() = 0;
};