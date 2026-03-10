#pragma once

class Component
{
public:
    enum class Type
    {
        Master,
        Remote,
        Webserver,
        Slave
    };

    Component(Type type) : type_(type) {}

    Type getType() const { return type_; }

private:
    Type type_;
};