#pragma once

/**
 * Interface for DMX Controller HTTP Task
 * Provides abstraction for dependency injection and testing
 */
class IDmxControllerHttpTask
{
public:
    virtual ~IDmxControllerHttpTask() = default;

    /**
     * Start the webserver and all its services
     */
    virtual void start() = 0;

    /**
     * Stop the webserver and all its services
     */
    virtual void stop() = 0;
};
