#pragma once

#include "core/ecs.hpp"

#include "component/transform.hpp"

class CameraOrbit : public Component
{
public:
    CameraOrbit();

    bool initialise();
    void update();

private:
    Transform* transform_;
};
