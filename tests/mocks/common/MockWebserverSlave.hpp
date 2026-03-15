#pragma once
#include "../../../main/slaves/webserver_slave/common/IWebserverSlave.hpp"

class MockWebserverSlave : public IWebserverSlave {
public:
    MockWebserverSlave() = default;
    ~MockWebserverSlave() override = default;
    void start() override {}
    void stop() override {}
};
