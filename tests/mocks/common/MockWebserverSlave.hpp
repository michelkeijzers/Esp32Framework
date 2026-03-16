#pragma once
#include "../../../main/common/nodes/webserver/common/IWebserverSlave.hpp"

class MockWebserverSlave : public IWebserverSlave {
public:
    MockWebserverSlave() = default;
    ~MockWebserverSlave() override = default;
    void start() override {}
    void stop() override {}
};
