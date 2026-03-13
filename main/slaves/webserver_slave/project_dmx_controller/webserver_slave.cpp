
#include "api_presets.cpp"
#include "api_config.cpp"
#include "api_status.cpp"

#include "webserver_slave.hpp"

WebserverSlave::WebserverSlave(IEspHttpServer& espHttpServer) 
: espHttpServer_(espHttpServer) 
{}

WebserverSlave::~WebserverSlave()
{
    stop();
}

void WebserverSlave::start()
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    if (httpd_start(&server, &config) == ESP_OK)
    {
        register_endpoints();
    }
}

void WebserverSlave::stop()
{
    if (server)
    {
        httpd_stop(server);
        server = NULL;
    }
}

void WebserverSlave::register_endpoints()
{
    // Register Presets endpoints
    httpd_uri_t presets_uri = {
        .uri = "/api/presets",
        .method = HTTP_GET,
        .handler = get_presets_handler,
        .user_ctx = NULL};
    httpd_register_uri_handler(server, &presets_uri);
    // Register Config endpoints
    httpd_uri_t config_uri = {
        .uri = "/api/configuration",
        .method = HTTP_GET,
        .handler = get_config_handler,
        .user_ctx = NULL};
    httpd_register_uri_handler(server, &config_uri);
    // Register Status endpoints
    httpd_uri_t status_uri = {
        .uri = "/api/status",
        .method = HTTP_GET,
        .handler = get_status_handler,
        .user_ctx = NULL};
    httpd_register_uri_handler(server, &status_uri);
    // ... Register more endpoints as needed ...
}
