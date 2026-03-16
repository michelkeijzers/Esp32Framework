#pragma once

#include "../common/component.hpp"
#include "../common/esp_now/EspNow.hpp"

class Master : Component
{
public:
    Master();
    ~Master();

    esp_err_t init();

private:
    EspNow espNowHandler_;
};