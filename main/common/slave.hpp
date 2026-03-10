#pragma once

#include "component.hpp"

class SlaveComponent : public Component
{
public:
    enum class Type
    {
        Gpio,
        Display,
        Dmx,
        Midi
    };

    SlaveComponent(Type type) : Component(Component::Type::Slave), type_(type) {}

    Type getType() const { return type_; }

private:
    Type type_;
};