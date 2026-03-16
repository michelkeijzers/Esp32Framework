#pragma once

#include "../../esp/esp_now/EspNow.hpp"

class Master
{
public:
    Master();
    ~Master();

    esp_err_t init();

private:
    EspNow espNowHandler_;
};
