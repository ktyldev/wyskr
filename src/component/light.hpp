#pragma once

#include "core/component.h"

class Light : public Component
{
public:
    Light();
    Light(Colour& colour);
    Light(Light& other);

    virtual bool initialise() = 0;

    void setColour(Colour& colour);
    Colour& getColour();

protected:
    Colour colour_;
};
