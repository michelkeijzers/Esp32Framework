#include "DmxControllerHttpTask.hpp"
#include "../../../common/esp/esp_logger/IEspLogger.hpp"
#include "../../../common/esp/esp_file_systems/IEspLittleFs.hpp"
#include "../../../common/esp/esp_http_server/IEspHttpServer.hpp"
#include "../../../common/esp/esp_nvs/IEspNvs.hpp"
#include "../presets_task/IPresetManager.hpp"
#include "apis/ApiPresets.hpp"
#include "apis/ApiPresetValues.hpp"
#include "apis/ApiConfig.hpp"


DmxControllerHttpTask::DmxControllerHttpTask(IEspLittleFs& espLittleFs, IEspHttpServer& espHttpServer, IEspNvs& nvsManager, IEspLogger& logger,
                                                                                                                 IApiStatus& apiStatus, IApiNodes& apiNodes, IApiSystem& apiSystem,
                                                                                                                 IApiFirmware& apiFirmware, IApiSecurity& apiSecurity, IApiLogging& apiLogging,
                                                                                                                 IApiConfig* apiConfig, IApiPresets* apiPresets, IApiPresetValues* apiPresetValues,
                                                                                                                 IPresetManager& presetManager)
        : Webserver(espLittleFs, espHttpServer, logger, apiStatus, apiNodes, apiSystem, apiFirmware, apiSecurity, apiLogging),
            nvsManager_(nvsManager), presetManager_(presetManager), apiConfig_(apiConfig), apiPresets_(apiPresets), apiPresetValues_(apiPresetValues)
{
}

DmxControllerHttpTask::~DmxControllerHttpTask()
{
}

void DmxControllerHttpTask::start()
{
    // Initialize NVS first (using injected manager)
    int ret = nvsManager_.nvs_flash_init();
    if (ret != ESP_OK)
    {
        logger_.log_error("DmxControllerHttpTask", "Failed to initialize NVS");
        // Continue anyway - NVS errors shouldn't prevent webserver from starting
    }

    // Load presets from NVS (using injected preset manager)
    ret = presetManager_.load_presets();
    if (ret != ESP_OK) {
        logger_.log_error("DmxControllerHttpTask", "Failed to load presets");
        // Continue anyway - preset loading shouldn't prevent webserver from starting
    }

    // Call base class start() which handles mount_littlefs and httpd_start
    Webserver::start();
}

void DmxControllerHttpTask::stop()
{
    // Call base class stop() which handles httpd_stop
    Webserver::stop();
}

void DmxControllerHttpTask::register_endpoints()
{
    // Register both generic endpoints (from base class) and DMX-specific endpoints
    register_endpoints_esp32();
}

// Static handler functions for dispatch - Presets
static esp_err_t presets_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->get_presets_handler(req);
}
static esp_err_t active_preset_numbers_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->get_active_preset_numbers_handler(req);
}
static esp_err_t select_preset_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->select_preset_handler(req);
}
static esp_err_t blackout_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->blackout_handler(req);
}
static esp_err_t save_preset_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->save_preset_handler(req);
}
static esp_err_t move_preset_up_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->move_preset_up_handler(req);
}
static esp_err_t move_preset_down_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->move_preset_down_handler(req);
}
static esp_err_t delete_preset_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->delete_preset_handler(req);
}
static esp_err_t insert_preset_at_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->insert_preset_at_handler(req);
}
static esp_err_t swap_preset_activation_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresets*>(req->user_ctx);
    return obj->swap_preset_activation_handler(req);
}

// Static handler functions for dispatch - Preset Values
static esp_err_t get_preset_values_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresetValues*>(req->user_ctx);
    return obj->get_preset_values_handler(req);
}
static esp_err_t set_preset_value_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiPresetValues*>(req->user_ctx);
    return obj->set_preset_value_handler(req);
}

// Static handler functions for dispatch - Config
static esp_err_t config_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiConfig*>(req->user_ctx);
    return obj->get_config_handler(req);
}
static esp_err_t put_config_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiConfig*>(req->user_ctx);
    return obj->put_config_handler(req);
}
static esp_err_t circular_navigation_handler_static(httpd_req_t *req) {
    auto* obj = static_cast<ApiConfig*>(req->user_ctx);
    return obj->set_circular_navigation_handler(req);
}

void DmxControllerHttpTask::register_dmx_endpoints()
{
    // GET /api/presets
    httpd_uri_t presets_uri = {
        .uri = "/api/v1/presets",
        .method = HTTP_GET,
        .handler = presets_handler_static,
        .user_ctx = apiPresets_};
    espHttpServer_.httpd_register_uri_handler(server, &presets_uri);

    // GET /api/active_preset_numbers
    httpd_uri_t active_preset_numbers_uri = {
        .uri = "/api/v1/active_preset_numbers",
        .method = HTTP_GET,
        .handler = active_preset_numbers_handler_static,
        .user_ctx = apiPresets_};
    espHttpServer_.httpd_register_uri_handler(server, &active_preset_numbers_uri);

    // POST /api/select_preset/*
    httpd_uri_t select_preset_uri = {
        .uri = "/api/v1/select_preset/*",
        .method = HTTP_POST,
        .handler = select_preset_handler_static,
        .user_ctx = apiPresets_};
    espHttpServer_.httpd_register_uri_handler(server, &select_preset_uri);

    // POST /api/blackout
    httpd_uri_t blackout_uri = {
        .uri = "/api/v1/blackout",
        .method = HTTP_POST,
        .handler = blackout_handler_static,
        .user_ctx = apiPresets_};
    espHttpServer_.httpd_register_uri_handler(server, &blackout_uri);

    // PUT /api/save_preset/*
    httpd_uri_t save_preset_uri = {
        .uri = "/api/v1/save_preset/*",
        .method = HTTP_PUT,
        .handler = save_preset_handler_static,
        .user_ctx = apiPresets_};
    espHttpServer_.httpd_register_uri_handler(server, &save_preset_uri);

    // PUT /api/presets/*/move_up
    httpd_uri_t move_preset_up_uri = {
        .uri = "/api/v1/presets/*/move_up",
        .method = HTTP_PUT,
        .handler = move_preset_up_handler_static,
        .user_ctx = apiPresets_};
    espHttpServer_.httpd_register_uri_handler(server, &move_preset_up_uri);

    // PUT /api/presets/*/move_down
    httpd_uri_t move_preset_down_uri = {
        .uri = "/api/v1/presets/*/move_down",
        .method = HTTP_PUT,
        .handler = move_preset_down_handler_static,
        .user_ctx = apiPresets_};
    espHttpServer_.httpd_register_uri_handler(server, &move_preset_down_uri);

    // DELETE /api/presets/*
    httpd_uri_t delete_preset_uri = {
        .uri = "/api/v1/presets/*",
        .method = HTTP_DELETE,
        .handler = delete_preset_handler_static,
        .user_ctx = apiPresets_};
    espHttpServer_.httpd_register_uri_handler(server, &delete_preset_uri);

    // POST /api/presets/*/insert_at
    httpd_uri_t insert_preset_at_uri = {
        .uri = "/api/v1/presets/*/insert_at",
        .method = HTTP_POST,
        .handler = insert_preset_at_handler_static,
        .user_ctx = apiPresets_};
    espHttpServer_.httpd_register_uri_handler(server, &insert_preset_at_uri);

    // PUT /api/presets/*/swap_activation
    httpd_uri_t swap_preset_activation_uri = {
        .uri = "/api/v1/presets/*/swap_activation",
        .method = HTTP_PUT,
        .handler = swap_preset_activation_handler_static,
        .user_ctx = apiPresets_};
    espHttpServer_.httpd_register_uri_handler(server, &swap_preset_activation_uri);

    // GET /api/preset_values/*
    httpd_uri_t get_preset_values_uri = {
        .uri = "/api/v1/preset_values/*",
        .method = HTTP_GET,
        .handler = get_preset_values_handler_static,
        .user_ctx = apiPresetValues_};
    espHttpServer_.httpd_register_uri_handler(server, &get_preset_values_uri);

    // PUT /api/preset_value/*/*
    httpd_uri_t set_preset_value_uri = {
        .uri = "/api/v1/preset_value/*/*",
        .method = HTTP_PUT,
        .handler = set_preset_value_handler_static,
        .user_ctx = apiPresetValues_};
    espHttpServer_.httpd_register_uri_handler(server, &set_preset_value_uri);

    // GET /api/configuration
    httpd_uri_t config_uri = {
        .uri = "/api/v1/configuration",
        .method = HTTP_GET,
        .handler = config_handler_static,
        .user_ctx = apiConfig_};
    espHttpServer_.httpd_register_uri_handler(server, &config_uri);

    // PUT /api/configuration
    httpd_uri_t put_config_uri = {
        .uri = "/api/v1/configuration",
        .method = HTTP_PUT,
        .handler = put_config_handler_static,
        .user_ctx = apiConfig_};
    espHttpServer_.httpd_register_uri_handler(server, &put_config_uri);

    // PUT /api/configuration_presets_circular_navigation
    httpd_uri_t circular_navigation_uri = {
        .uri = "/api/v1/configuration_presets_circular_navigation",
        .method = HTTP_PUT,
        .handler = circular_navigation_handler_static,
        .user_ctx = apiConfig_};
    espHttpServer_.httpd_register_uri_handler(server, &circular_navigation_uri);
}

void DmxControllerHttpTask::register_endpoints_esp32()
{
    // Register all DMX-specific endpoints
    register_dmx_endpoints();
    
    // Register generic endpoints from base class
    register_generic_endpoints();
    
    // Register static file handler
    register_static_file_handler();
}

void DmxControllerHttpTask::register_endpoints_test()
{
    // For testing, register the same endpoints as in production
    register_endpoints_esp32();
}
