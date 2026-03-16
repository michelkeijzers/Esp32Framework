#include "EspNow.hpp"
#include <cstring>

#ifdef ESP_PLATFORM
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_log.h"

static const char* TAG = "EspNow";

EspNow::EspNow() : initialized_(false)
{
}

EspNow::~EspNow()
{
    deinit();
}

esp_err_t EspNow::init()
{
    if (initialized_) {
        return ESP_OK;
    }

    esp_err_t ret = esp_now_init();
    if (ret == ESP_OK) {
        initialized_ = true;
        ESP_LOGI(TAG, "ESP-NOW initialized successfully");
    } else {
        ESP_LOGE(TAG, "Failed to initialize ESP-NOW: %s", esp_err_to_name(ret));
    }
    return ret;
}

esp_err_t EspNow::deinit()
{
    if (!initialized_) {
        return ESP_OK;
    }

    esp_err_t ret = esp_now_deinit();
    if (ret == ESP_OK) {
        initialized_ = false;
        ESP_LOGI(TAG, "ESP-NOW deinitialized successfully");
    }
    return ret;
}

esp_err_t EspNow::connectPeer(const uint8_t *peer_addr)
{
    if (!initialized_) {
        ESP_LOGE(TAG, "ESP-NOW not initialized");
        return ESP_FAIL;
    }

    esp_now_peer_info_t peer_info = {};
    peer_info.channel = 0;

    memcpy(peer_info.peer_addr, peer_addr, 6);

    esp_err_t ret = esp_now_add_peer(&peer_info);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Peer added successfully");
    } else {
        ESP_LOGE(TAG, "Failed to add peer: %s", esp_err_to_name(ret));
    }
    return ret;
}

esp_err_t EspNow::disconnectPeer(const uint8_t *peer_addr)
{
    if (!initialized_) {
        ESP_LOGE(TAG, "ESP-NOW not initialized");
        return ESP_FAIL;
    }

    esp_err_t ret = esp_now_del_peer(peer_addr);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Peer removed successfully");
    } else {
        ESP_LOGE(TAG, "Failed to remove peer: %s", esp_err_to_name(ret));
    }
    return ret;
}

esp_err_t EspNow::sendMessage(const uint8_t *data, size_t len)
{
    if (!initialized_) {
        ESP_LOGE(TAG, "ESP-NOW not initialized");
        return ESP_FAIL;
    }

    if (len > ESP_NOW_MAX_DATA_LEN) {
        ESP_LOGE(TAG, "Message too large: %zu > %d", len, ESP_NOW_MAX_DATA_LEN);
        return ESP_FAIL;
    }

    esp_err_t ret = esp_now_send(nullptr, data, len);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Message sent successfully");
    } else {
        ESP_LOGE(TAG, "Failed to send message: %s", esp_err_to_name(ret));
    }
    return ret;
}

#else
// Stub implementations for non-ESP32 platforms

EspNow::EspNow() : initialized_(false)
{
}

EspNow::~EspNow()
{
}

esp_err_t EspNow::init()
{
    initialized_ = true;
    return ESP_OK;
}

esp_err_t EspNow::deinit()
{
    initialized_ = false;
    return ESP_OK;
}

esp_err_t EspNow::connectPeer(const uint8_t *peer_addr)
{
    return ESP_OK;
}

esp_err_t EspNow::disconnectPeer(const uint8_t *peer_addr)
{
    return ESP_OK;
}

esp_err_t EspNow::sendMessage(const uint8_t *data, size_t len)
{
    return ESP_OK;
}

#endif
