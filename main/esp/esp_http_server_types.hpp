#pragma once

#ifdef ESP_PLATFORM
#include "esp_http_server.h"
#else
// Stand-in types for non-ESP32 platforms
struct httpd_req {};
typedef struct httpd_req httpd_req_t;
#endif
