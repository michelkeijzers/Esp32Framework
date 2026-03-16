#include "MockEspNow.hpp"

MockEspNow::MockEspNow() : initialized_(false)
{
}

esp_err_t MockEspNow::init()
{
    initialized_ = true;
    return ESP_OK;
}

esp_err_t MockEspNow::deinit()
{
    initialized_ = false;
    peers_.clear();
    sent_messages_.clear();
    return ESP_OK;
}

esp_err_t MockEspNow::connectPeer(const uint8_t *peer_addr)
{
    if (!initialized_) {
        return ESP_FAIL;
    }

    // Check if peer already exists
    if (hasPeer(peer_addr)) {
        return ESP_FAIL;  // Peer already connected
    }

    std::vector<uint8_t> peer(peer_addr, peer_addr + 6);
    peers_.push_back(peer);
    return ESP_OK;
}

esp_err_t MockEspNow::disconnectPeer(const uint8_t *peer_addr)
{
    if (!initialized_) {
        return ESP_FAIL;
    }

    for (auto it = peers_.begin(); it != peers_.end(); ++it) {
        if (std::memcmp(it->data(), peer_addr, 6) == 0) {
            peers_.erase(it);
            return ESP_OK;
        }
    }
    return ESP_FAIL;  // Peer not found
}

esp_err_t MockEspNow::sendMessage(const uint8_t *data, size_t len)
{
    if (!initialized_) {
        return ESP_FAIL;
    }

    if (len > 250) {
        return ESP_FAIL;  // Message too large
    }

    std::vector<uint8_t> message(data, data + len);
    sent_messages_.push_back(message);
    return ESP_OK;
}

bool MockEspNow::hasPeer(const uint8_t *peer_addr) const
{
    for (const auto& peer : peers_) {
        if (std::memcmp(peer.data(), peer_addr, 6) == 0) {
            return true;
        }
    }
    return false;
}
