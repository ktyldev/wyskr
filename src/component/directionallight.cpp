#include "directionallight.hpp"

DirectionalLight::DirectionalLight() : 
    direction_(glm::vec3())
{
}

DirectionalLight::DirectionalLight(glm::vec3 direction) :
    direction_(direction)
{
}

void DirectionalLight::setDirection(glm::vec3 direction)
{
    direction_ = direction;
}

glm::vec3 DirectionalLight::getDirection()
{
    return direction_;
}

