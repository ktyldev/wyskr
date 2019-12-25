#pragma once

#include "core/ecs.hpp"
#include "core/materialrepo.hpp"

class Scene
{
public:
    Scene();

    bool load(EntityComponentSystem& ecs, MaterialRepo& materials);
};

