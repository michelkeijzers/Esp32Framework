#pragma once


class MockDmxControllerWebserverSlave : public IDmxControllerWebserverSlave {
public:
    MockDmxControllerWebserverSlave() = default;
    ~MockDmxControllerWebserverSlave() override = default;
    void start() override {}
    void stop() override {}
};
