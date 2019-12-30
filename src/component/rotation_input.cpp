
#include "rotation_input.hpp"

#include "framework.hpp"

RotationInput::RotationInput() :
    input_(nullptr),
    transform_(nullptr)
{
}

bool RotationInput::initialise()
{
    input_ = &Framework::instance()->input();
    transform_ = &(entity()->getComponent<Transform>());

    up_     = SDLK_w;
    left_   = SDLK_a;
    down_   = SDLK_s;
    right_  = SDLK_d;

    input_->registerKey(up_);
    input_->registerKey(left_);
    input_->registerKey(down_);
    input_->registerKey(right_);

    return transform_ != nullptr && input_ != nullptr;
}

void RotationInput::update()
{
    float speed = 1.0f * Time::deltaTime();

    glm::vec2 rot = rotation();

    transform_->rotate(speed * rot.x, glm::vec3(0, 1, 0));
    transform_->rotate(speed * rot.y, glm::vec3(1, 0, 0));
}

glm::vec2 RotationInput::rotation()
{
    glm::vec2 result;

    result.x = axis(input_->isPressed(left_), input_->isPressed(right_));
    result.y = axis(input_->isPressed(up_), input_->isPressed(down_));

    return result;
}

float RotationInput::axis(bool negative, bool positive)
{
    float result = 0;

    if (negative)
    {
        --result;
    }

    if (positive)
    {
        ++result;
    }

    return result;
}

