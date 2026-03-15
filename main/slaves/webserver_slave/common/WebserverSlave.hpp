#pragma once

#include <memory>
#include "../../../common/esp_http_server/esp_http_server_if.hpp"
#include "../common/apis/StaticFileHandler.hpp"

class IEspLittleFs;
class IEspHttpServer;
class IEspLogger;

class ApiStatus;
class ApiNodes;
class ApiSystem;
class ApiFirmware;
class ApiSecurity;
class ApiLogging;

/**
 * Base WebserverSlave class with common functionality for all webserver implementations
 * Handles LittleFS mounting, static file serving, and generic API registration
 * Derived classes can override register_endpoints() to add project-specific endpoints
 */
class WebserverSlave
{
public:
    explicit WebserverSlave(IEspLittleFs& espLittleFs, IEspHttpServer& espHttpServer, IEspLogger& logger);
    virtual ~WebserverSlave();

    virtual void start();
    void stop();

    void init_generic_apis();
    void cleanup_generic_apis();

    // Thunk for static file handler
    static esp_err_t static_file_handler_thunk(httpd_req_t *req);


protected:
    // Order matters for -Werror=reorder: server must come before API pointers

    IEspLittleFs& espLittleFs_;
    IEspHttpServer& espHttpServer_;
    IEspLogger& logger_;

    ApiStatus* apiStatus_;
    ApiNodes* apiNodes_;
    ApiSystem* apiSystem_;
    ApiFirmware* apiFirmware_;
    ApiSecurity* apiSecurity_;
    ApiLogging* apiLogging_;

#ifndef UNIT_TEST
    httpd_handle_t server;
#else
    void* server = nullptr;  // Dummy for unit tests
#endif
    void mount_littlefs();
    void register_static_file_handler();
    
    /**
     * Virtual method to register endpoints
     * Base implementation registers generic APIs and static file handler
     * Derived classes can override to add project-specific endpoints
     */
    virtual void register_endpoints();
    virtual void register_generic_endpoints();

    // Non-static member for static file handler
    esp_err_t static_file_handler(httpd_req_t *req);

private:
};
