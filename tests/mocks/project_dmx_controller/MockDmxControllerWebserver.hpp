#pragma once
#include "../../main/projects/dmx_controller/http_task/IDmxControllerWebserver.h"

class MockDmxControllerWebserver : public IDmxControllerWebserver
{
  public:
    MockDmxControllerWebserver() = default;
    ~MockDmxControllerWebserver() override = default;
    void start() override {}
    void stop() override {}
};
