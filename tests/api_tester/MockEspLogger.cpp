#include "MockEspLogger.hpp"

void MockEspLogger::log_error(const char* tag, const char* message)
{
    logs_.push_back({"ERROR", tag, message});
}

void MockEspLogger::log_info(const char* tag, const char* message)
{
    logs_.push_back({"INFO", tag, message});
}

void MockEspLogger::log_warn(const char* tag, const char* message)
{
    logs_.push_back({"WARN", tag, message});
}

bool MockEspLogger::has_error(const char* tag, const char* message) const
{
    for (const auto& entry : logs_) {
        if (entry.level == "ERROR" && entry.tag == tag && entry.message == message) {
            return true;
        }
    }
    return false;
}

bool MockEspLogger::has_info(const char* tag, const char* message) const
{
    for (const auto& entry : logs_) {
        if (entry.level == "INFO" && entry.tag == tag && entry.message == message) {
            return true;
        }
    }
    return false;
}

bool MockEspLogger::has_warn(const char* tag, const char* message) const
{
    for (const auto& entry : logs_) {
        if (entry.level == "WARN" && entry.tag == tag && entry.message == message) {
            return true;
        }
    }
    return false;
}
