#pragma once
#include "../main/slaves/webserver_slave/dmx_controller/IDmxControllerWebserverSlave.hpp"

class MockDmxControllerWebserverSlave : public IDmxControllerWebserverSlave {
public:
    MockDmxControllerWebserverSlave() = default;
    ~MockDmxControllerWebserverSlave() override = default;
    void start() override {}
    void stop() override {}
};
