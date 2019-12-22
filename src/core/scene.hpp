#pragma once

#include "core/ecs.hpp"

class Scene
{
public:
    Scene();

    bool load(EntityComponentSystem& ecs);
};

