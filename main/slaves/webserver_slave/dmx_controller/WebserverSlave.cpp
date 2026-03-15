
// DEPRECATED FILE - No longer used
// This file has been replaced by:
// - common/WebserverSlave.cpp (base class)
// - Dmx ControllerWebserverSlave.cpp (derived class)
// 
// See DmxControllerWebserverSlave.hpp for implementation details.

Web serverSlave::~WebserverSlave()
{
}

void WebserverSlave::start()
{
}

void WebserverSlave::stop()
{
}


// Handler stubs - see DmxControllerWebserverSlave.cpp for actual implementation
static esp_err_t presets_handler_static(httpd_req_t *req) { return ESP_OK; }
static esp_err_t active_preset_numbers_handler_static(httpd_req_t *req) { return ESP_OK; }
static esp_err_t select_preset_handler_static(httpd_req_t *req) { return ESP_OK; }
static esp_err_t blackout_handler_static(httpd_req_t *req) { return ESP_OK; }
static esp_err_t save_preset_handler_static(httpd_req_t *req) { return ESP_OK; }
static esp_err_t move_preset_up_handler_static(httpd_req_t *req) { return ESP_OK; }
static esp_err_t move_preset_down_handler_static(httpd_req_t *req) { return ESP_OK; }
static esp_err_t delete_preset_handler_static(httpd_req_t *req) { return ESP_OK; }
static esp_err_t insert_preset_at_handler_static(httpd_req_t *req) { return ESP_OK; }
// All remaining handler implementations moved to DmxControllerWebserverSlave.cpp


// All remaining method implementations moved to DmxControllerWebserverSlave
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

    // GET /api/status
    httpd_uri_t status_uri = {
        .uri = "/api/v1/status",
        .method = HTTP_GET,
        .handler = status_handler_static,
        .user_ctx = apiStatus_};
    espHttpServer_.httpd_register_uri_handler(server, &status_uri);

    // GET /api/status/stream
    httpd_uri_t status_stream_uri = {
        .uri = "/api/v1/status/stream",
        .method = HTTP_GET,
        .handler = status_stream_handler_static,
        .user_ctx = apiStatus_};
    espHttpServer_.httpd_register_uri_handler(server, &status_stream_uri);

    // GET /api/nodes_info
    httpd_uri_t nodes_info_uri = {
        .uri = "/api/v1/nodes_info",
        .method = HTTP_GET,
        .handler = nodes_info_handler_static,
        .user_ctx = apiNodes_};
    espHttpServer_.httpd_register_uri_handler(server, &nodes_info_uri);

    // POST /api/nodes_info
    httpd_uri_t save_nodes_info_uri = {
        .uri = "/api/v1/nodes_info",
        .method = HTTP_POST,
        .handler = save_nodes_info_handler_static,
        .user_ctx = apiNodes_};
    espHttpServer_.httpd_register_uri_handler(server, &save_nodes_info_uri);

    // POST /api/reboot
    httpd_uri_t reboot_uri = {
        .uri = "/api/v1/reboot",
        .method = HTTP_POST,
        .handler = reboot_handler_static,
        .user_ctx = apiSystem_};
    espHttpServer_.httpd_register_uri_handler(server, &reboot_uri);

    // POST /api/factory_reset
    httpd_uri_t factory_reset_uri = {
        .uri = "/api/v1/factory_reset",
        .method = HTTP_POST,
        .handler = factory_reset_handler_static,
        .user_ctx = apiSystem_};
    espHttpServer_.httpd_register_uri_handler(server, &factory_reset_uri);

    // POST /api/firmware_chunk/*
    httpd_uri_t firmware_chunk_uri = {
        .uri = "/api/v1/firmware_chunk/*",
        .method = HTTP_POST,
        .handler = firmware_chunk_handler_static,
        .user_ctx = apiFirmware_};
    espHttpServer_.httpd_register_uri_handler(server, &firmware_chunk_uri);

    // POST /api/firmware_finish/*
    httpd_uri_t firmware_finish_uri = {
        .uri = "/api/v1/firmware_finish/*",
        .method = HTTP_POST,
        .handler = firmware_finish_handler_static,
        .user_ctx = apiFirmware_};
    espHttpServer_.httpd_register_uri_handler(server, &firmware_finish_uri);

    // POST /api/esp_now_key
    httpd_uri_t esp_now_key_uri = {
        .uri = "/api/v1/esp_now_key",
        .method = HTTP_POST,
        .handler = esp_now_key_handler_static,
        .user_ctx = apiSecurity_};
    espHttpServer_.httpd_register_uri_handler(server, &esp_now_key_uri);

    // POST /api/wifi_password
    httpd_uri_t wifi_password_uri = {
        .uri = "/api/v1/wifi_password",
        .method = HTTP_POST,
        .handler = wifi_password_handler_static,
        .user_ctx = apiSecurity_};
    espHttpServer_.httpd_register_uri_handler(server, &wifi_password_uri);

    // GET /api/logging
    httpd_uri_t logging_uri = {
        .uri = "/api/v1/logging",
        .method = HTTP_GET,
        .handler = logging_handler_static,
        .user_ctx = apiLogging_};
    espHttpServer_.httpd_register_uri_handler(server, &logging_uri);

    // Register static file handler for serving web UI from LittleFS
    // This must be registered AFTER all API endpoints so API calls take precedence
    httpd_uri_t static_file_uri = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = WebserverSlave::static_file_handler_thunk,
        .user_ctx = this};
    espHttpServer_.httpd_register_uri_handler(server, &static_file_uri);

}

void WebserverSlave::mount_littlefs()
{
    // LittleFS configuration
    esp_vfs_littlefs_conf_t conf = {
        .base_path = "/littlefs",
        .partition_label = "littlefs",
        .partition = NULL,
#if defined(CONFIG_LITTLEFS_SDMMC_SUPPORT)
        .sdcard = NULL,
#endif
        .format_if_mount_failed = false,
        .read_only = false,
        .dont_mount = false,
        .grow_on_mount = false
    };

    // Mount LittleFS
    esp_err_t ret = espLittleFs_.esp_littlefs_mount(&conf);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            // Could not mount, format and try again
            espLittleFs_.esp_littlefs_format("littlefs");
            ret = espLittleFs_.esp_littlefs_mount(&conf);
        }

        if (ret != ESP_OK) {
            // Mounting failed despite format attempt; log error but continue
            // The webserver will still work, just without static files
            printf("Error mounting LittleFS: %s\n", esp_err_to_name(ret));
        } else {
            printf("LittleFS mounted successfully\n");
        }
    } else {
        printf("LittleFS mounted successfully\n");
    }
}



