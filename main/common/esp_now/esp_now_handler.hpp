#pragma once

#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_err.h"

class EspNowHandler
{
public:
    EspNowHandler();
    ~EspNowHandler();

    esp_err_t init();
    esp_err_t connectPeer(const uint8_t *peer_addr);
    esp_err_t sendMessage(const uint8_t *data, size_t len);
};