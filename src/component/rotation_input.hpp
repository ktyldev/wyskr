#pragma once

#include "core/component.hpp"
#include "core/keyboard_input.hpp"
#include "core/math.hpp"

#include "component/transform.hpp"

class RotationInput : public Component 
{
public:
    RotationInput();

    bool initialise();
    void update();

private:
    KeyboardInput*  input_;
    Transform*      transform_;

    int    left_;
    int    right_;
    int    up_;
    int    down_;

    glm::vec2 rotation();
    float axis(bool negative, bool positive);
};
