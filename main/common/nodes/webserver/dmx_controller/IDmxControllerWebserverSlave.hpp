#pragma once

/**
 * Interface for DMX Controller Webserver Slave
 * Provides abstraction for dependency injection and testing
 */
class IDmxControllerWebserverSlave
{
public:
    virtual ~IDmxControllerWebserverSlave() = default;

    /**
     * Start the webserver slave and all its services
     */
    virtual void start() = 0;

    /**
     * Stop the webserver slave and all its services
     */
    virtual void stop() = 0;
};
