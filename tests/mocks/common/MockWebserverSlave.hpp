#pragma once
#include "../../../main/common/nodes/webserver/common/IWebserver.hpp"

class MockWebserver : public IWebserver {
public:
    MockWebserver() = default;
    ~MockWebserver() override = default;
    void start() override {}
    void stop() override {}
};
