#pragma once
#include "../../../main/common/nodes/webserver/webserver_task/IWebserver.hpp"

class MockWebserver : public IWebserver {
public:
    MockWebserver() = default;
    ~MockWebserver() override = default;
    void start() override {}
    void stop() override {}
};
