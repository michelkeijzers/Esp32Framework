#pragma once

/**
 * Interface for WebserverSlave for DI and testing
 */
class IWebserverSlave {
public:
    virtual ~IWebserverSlave() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
};
