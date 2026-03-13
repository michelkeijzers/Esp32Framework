
#include "ApiPresets.cpp"
#include "ApiConfig.cpp"
#include "ApiStatus.cpp"

#include "WebserverSlave.hpp"


#include "ApiConfig.hpp"
#include "ApiPresets.hpp"
#include "ApiStatus.hpp"

WebserverSlave::WebserverSlave(IEspHttpServer& espHttpServer)
    : espHttpServer_(espHttpServer)
{
    apiConfig_ = new ApiConfig(espHttpServer_);
    apiPresets_ = new ApiPresets(espHttpServer_);
    apiStatus_ = new ApiStatus(espHttpServer_);
}

WebserverSlave::~WebserverSlave()
{
    stop();
    delete apiConfig_;
    delete apiPresets_;
    delete apiStatus_;    
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

// Static handler functions for dispatch
static esp_err_t presets_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->get_presets_handler(req);
}
static esp_err_t config_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiConfig*>(req->user_ctx);
    return obj->get_config_handler(req);
}
static esp_err_t status_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiStatus*>(req->user_ctx);
    return obj->get_status_handler(req);
}

void WebserverSlave::register_endpoints()
{
    // Register Presets endpoints
    httpd_uri_t presets_uri = {
        .uri = "/api/presets",
        .method = HTTP_GET,
        .handler = presets_handler_static,
        .user_ctx = apiPresets_};
    httpd_register_uri_handler(server, &presets_uri);

    // Register Config endpoints
    httpd_uri_t config_uri = {
        .uri = "/api/configuration",
        .method = HTTP_GET,
        .handler = config_handler_static,
        .user_ctx = apiConfig_};
    httpd_register_uri_handler(server, &config_uri);

    // Register Status endpoints
    httpd_uri_t status_uri = {
        .uri = "/api/status",
        .method = HTTP_GET,
        .handler = status_handler_static,
        .user_ctx = apiStatus_};
    httpd_register_uri_handler(server, &status_uri);

    // ... Register more endpoints as needed ...
}
