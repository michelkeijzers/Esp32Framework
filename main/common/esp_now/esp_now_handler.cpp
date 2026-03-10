#include "esp_now_handler.hpp"
#include "esp_log.h"
#include <cstring>

EspNowHandler::EspNowHandler()
{
}

EspNowHandler::~EspNowHandler()
{
}

esp_err_t EspNowHandler::init()
{
    esp_err_t ret = ESP_OK;

    ret = esp_netif_init();
    if (ret != ESP_OK)
    {
        ESP_LOGE("EspNowHandler", "Failed to initialize network interface: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = esp_event_loop_create_default();
    if (ret != ESP_OK)
    {
        ESP_LOGE("EspNowHandler", "Failed to create event loop: %s", esp_err_to_name(ret));
        return ret;
    }

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ret = esp_wifi_init(&cfg);
    if (ret != ESP_OK)
    {
        ESP_LOGE("EspNowHandler", "Failed to initialize WiFi: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = esp_wifi_set_mode(WIFI_MODE_STA);
    if (ret != ESP_OK)
    {
        ESP_LOGE("EspNowHandler", "Failed to set WiFi mode: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = esp_wifi_start();
    if (ret != ESP_OK)
    {
        ESP_LOGE("EspNowHandler", "Failed to start WiFi: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = esp_now_init();
    if (ret != ESP_OK)
    {
        ESP_LOGE("EspNowHandler", "Failed to initialize ESP-NOW: %s", esp_err_to_name(ret));
        return ret;
    }

    return ESP_OK;
}

esp_err_t EspNowHandler::connectPeer(const uint8_t *peer_addr)
{
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, peer_addr, ESP_NOW_ETH_ALEN);
    peerInfo.channel = 0;
    peerInfo.ifidx = WIFI_IF_STA;
    peerInfo.encrypt = false;
    esp_err_t ret = esp_now_add_peer(&peerInfo);
    if (ret != ESP_OK)
    {
        ESP_LOGE("EspNowHandler", "Failed to add peer: %s", esp_err_to_name(ret));
        return ret;
    }
    return ESP_OK;
}

esp_err_t EspNowHandler::sendMessage(const uint8_t *data, size_t len)
{
    uint8_t peer_addr[ESP_NOW_ETH_ALEN] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC}; // TODO: MAC Address
    esp_err_t ret = esp_now_send(peer_addr, data, len);
    if (ret != ESP_OK)
    {
        ESP_LOGE("EspNowHandler", "Failed to send message: %s", esp_err_to_name(ret));
        return ret;
    }
    return ESP_OK;
}
