#pragma once

#include "light.hpp"

class AmbientLight : public Light
{
public:
    AmbientLight();
    AmbientLight(Colour& colour);
    AmbientLight(AmbientLight& other);

    bool initialise();
};
