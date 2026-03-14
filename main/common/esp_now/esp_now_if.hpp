#pragma once

#ifdef ESP_PLATFORM
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_err.h"
#else
// Stand-in types for non-ESP32 platforms
typedef unsigned char uint8_t;
typedef int esp_err_t;

#define ESP_OK 0
#define ESP_FAIL 1

#define ESP_NOW_MAX_TOTAL_PEER_NUM 20
#define ESP_NOW_MAX_DATA_LEN 250


typedef int wifi_second_chan_t; // Add this typedef for host builds
typedef struct {
    uint8_t channel;
    wifi_second_chan_t second_channel;
} esp_now_peer_info_t;

#endif
