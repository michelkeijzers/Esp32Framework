#include "master.hpp"

Master::Master() : Component(Component::Type::Master), espNowHandler_()
{
}

Master::~Master()
{
}

esp_err_t Master::init()
{
    return espNowHandler_.init();
}
