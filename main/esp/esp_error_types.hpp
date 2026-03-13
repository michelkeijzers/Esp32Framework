#pragma once

#ifdef ESP_PLATFORM
#include "esp_err.h"
#else
// Stand-in types for non-ESP32 platforms
typedef int esp_err_t;
#endif
