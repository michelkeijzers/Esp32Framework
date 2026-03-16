#pragma once

/**
 * Interface for DMX Controller Webserver
 * Provides abstraction for dependency injection and testing
 */
class IDmxControllerWebserver
{
public:
    virtual ~IDmxControllerWebserver() = default;

    /**
     * Start the webserver and all its services
     */
    virtual void start() = 0;

    /**
     * Stop the webserver and all its services
     */
    virtual void stop() = 0;
};
