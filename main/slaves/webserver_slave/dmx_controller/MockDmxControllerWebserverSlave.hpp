#pragma once

#include "IDmxControllerWebserverSlave.hpp"

/**
 * Mock implementation of IDmxControllerWebserverSlave for testing purposes
 */
class MockDmxControllerWebserverSlave : public IDmxControllerWebserverSlave
{
public:
    MockDmxControllerWebserverSlave() = default;
    ~MockDmxControllerWebserverSlave() override = default;

    void start() override
    {
        // Mock implementation - do nothing
    }

    void stop() override
    {
        // Mock implementation - do nothing
    }
};
