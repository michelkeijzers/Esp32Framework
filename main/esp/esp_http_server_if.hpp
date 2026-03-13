#pragma once


#ifdef ESP_PLATFORM
#include "esp_http_server.h"
#else
#include <string>



// Stand-in types for non-ESP32 platforms
struct httpd_req {};

struct httpd_req_t {
    std::string response;
    std::string content_type;
};


#endif
