#pragma once
#include "../../../main/common/esp_logger/IEspLogger.hpp"
#include <vector>
#include <string>

/**
 * Mock implementation of IEspLogger for unit testing
 */
class MockEspLogger : public IEspLogger {
public:
    MockEspLogger() = default;
    virtual ~MockEspLogger() = default;

    void log_error(const char* tag, const char* message) override;
    void log_info(const char* tag, const char* message) override;
    void log_warn(const char* tag, const char* message) override;

    // Helper methods for testing
    struct LogEntry {
        std::string level;
        std::string tag;
        std::string message;
    };

    const std::vector<LogEntry>& get_logs() const { return logs_; }
    void clear_logs() { logs_.clear(); }
    bool has_error(const char* tag, const char* message) const;
    bool has_info(const char* tag, const char* message) const;
    bool has_warn(const char* tag, const char* message) const;

private:
    std::vector<LogEntry> logs_;
};
