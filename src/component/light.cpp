#include "light.hpp"

Light::Light() :
    colour_()
{
}

Light::Light(Colour& colour) :
    colour_(colour)
{
}

Light::Light(Light& other) :
    colour_(other.getColour())
{
}

bool Light::initialise()
{
    return true;
}

Colour& Light::getColour()
{
    return colour_;
}
