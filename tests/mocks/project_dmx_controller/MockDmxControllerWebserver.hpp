#pragma once
#include "../../main/projects/dmx_controller/http_task/IDmxControllerHttpTask.h"

class MockDmxControllerWebserver : public IDmxControllerHttpTask {
public:
    MockDmxControllerWebserver() = default;
    ~MockDmxControllerWebserver() override = default;
    void start() override {}
    void stop() override {}
};
