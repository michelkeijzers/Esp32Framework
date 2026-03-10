#pragma once

#include "../common/component.hpp"
#include "../common/esp_now/esp_now_handler.hpp"

class Master : Component
{
public:
    Master();
    ~Master();

    esp_err_t init();

private:
    EspNowHandler espNowHandler_;
};