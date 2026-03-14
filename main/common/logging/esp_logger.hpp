#pragma once

/**
 * Logging utility for ESP32
 * Wraps esp_log.h and provides simple logging interface
 * Safe to use in both ESP32 and unit test builds
 */

void esp_log_error(const char* tag, const char* message);
void esp_log_info(const char* tag, const char* message);
void esp_log_warn(const char* tag, const char* message);
