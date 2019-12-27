#include "rotate.hpp"

#include "core/time.hpp"

Rotate::Rotate() 
{
}

bool Rotate::initialise()
{
    transform_ = &(entity()->getComponent<Transform>());

    return transform_ != nullptr;
}

void Rotate::update()
{
    float angle = 1.0f;

    transform_->rotate(angle * Time::deltaTime(), glm::vec3(0, 1, 0));
}
