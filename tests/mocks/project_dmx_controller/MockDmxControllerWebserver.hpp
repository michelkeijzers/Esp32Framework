#pragma once
#include "../../../main/common/nodes/webserver/webserver_task/IDmxControllerWebserver.hpp"

class MockDmxControllerWebserver : public IDmxControllerWebserver {
public:
    MockDmxControllerWebserver() = default;
    ~MockDmxControllerWebserver() override = default;
    void start() override {}
    void stop() override {}
};
