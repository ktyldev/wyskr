#include "ambientlight.hpp"

AmbientLight::AmbientLight() : 
    Light()
{
}

AmbientLight::AmbientLight(Colour& colour) : 
    Light(colour)
{
}

AmbientLight::AmbientLight(AmbientLight& other) : 
    Light(other)
{
}

bool AmbientLight::initialise()
{
    return true;
}
