#pragma once

#include "light.hpp"

class DirectionalLight : public Light
{
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 direction);

    void setDirection(glm::vec3 direction);
    glm::vec3 getDirection();

private:
    glm::vec3 direction_;
};
