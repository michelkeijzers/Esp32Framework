#pragma once
#include "IEspNowHandler.hpp"

// Concrete implementation of ESP-NOW handler for ESP32
class EspNowHandler : public IEspNowHandler {
public:
    EspNowHandler();
    ~EspNowHandler();

    esp_err_t init() override;
    esp_err_t deinit() override;
    esp_err_t connectPeer(const uint8_t *peer_addr) override;
    esp_err_t disconnectPeer(const uint8_t *peer_addr) override;
    esp_err_t sendMessage(const uint8_t *data, size_t len) override;

private:
    bool initialized_;
};
