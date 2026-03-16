#pragma once
#include "../../../main/common/nodes/webserver/http_task/IApiServer.hpp"

class MockWebserver : public IApiServer {
public:
    MockWebserver() = default;
    ~MockWebserver() override = default;
    void start() override {}
    void stop() override {}
};
