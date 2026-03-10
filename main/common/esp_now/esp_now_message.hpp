#pragma once

#include <cstdint>

class EspNowMessage
{
public:
    EspNowMessage() = default;
    virtual ~EspNowMessage() = default;

    uint8_t getVersionNumber() const { return versionNumber_; }
    void setVersionNumber(uint8_t version) { versionNumber_ = version; }

    uint8_t getSequenceNumber() const { return sequenceNumber_; }
    void setSequenceNumber(uint8_t sequence) { sequenceNumber_ = sequence; }

    uint16_t getCrc16Checksum() const { return crc16Checksum_; }
    void setCrc16Checksum(uint16_t crc) { crc16Checksum_ = crc; }

private:
    uint8_t versionNumber_;
    uint8_t sequenceNumber_;
    uint16_t crc16Checksum_;
};