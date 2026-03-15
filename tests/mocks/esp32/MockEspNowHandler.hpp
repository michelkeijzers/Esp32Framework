#pragma once
#include "../../../main/common/esp_now/IEspNowHandler.hpp"
#include <vector>
#include <cstring>

// Mock implementation for unit testing
class MockEspNowHandler : public IEspNowHandler {
public:
    MockEspNowHandler();
    ~MockEspNowHandler() = default;

    esp_err_t init() override;
    esp_err_t deinit() override;
    esp_err_t connectPeer(const uint8_t *peer_addr) override;
    esp_err_t disconnectPeer(const uint8_t *peer_addr) override;
    esp_err_t sendMessage(const uint8_t *data, size_t len) override;

    // Test helpers
    bool isInitialized() const { return initialized_; }
    int getPeerCount() const { return peers_.size(); }
    const std::vector<std::vector<uint8_t>>& getSentMessages() const { return sent_messages_; }
    bool hasPeer(const uint8_t *peer_addr) const;
    void clearSentMessages() { sent_messages_.clear(); }

private:
    bool initialized_;
    std::vector<std::vector<uint8_t>> peers_;
    std::vector<std::vector<uint8_t>> sent_messages_;
};
