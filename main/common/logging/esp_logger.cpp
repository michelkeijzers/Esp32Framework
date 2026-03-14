#include "esp_logger.hpp"

#ifndef UNIT_TEST
#include "esp_log.h"

void esp_log_error(const char* tag, const char* message)
{
    ESP_LOGE(tag, "%s", message);
}

void esp_log_info(const char* tag, const char* message)
{
    ESP_LOGI(tag, "%s", message);
}

void esp_log_warn(const char* tag, const char* message)
{
    ESP_LOGW(tag, "%s", message);
}
#else
// Unit test stubs - just log to stderr
#include <cstdio>

void esp_log_error(const char* tag, const char* message)
{
    fprintf(stderr, "[E][%s] %s\n", tag, message);
}

void esp_log_info(const char* tag, const char* message)
{
    fprintf(stderr, "[I][%s] %s\n", tag, message);
}

void esp_log_warn(const char* tag, const char* message)
{
    fprintf(stderr, "[W][%s] %s\n", tag, message);
}
#endif
