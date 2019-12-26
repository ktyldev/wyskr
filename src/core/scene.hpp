#pragma once

#include "core/ecs.hpp"
#include "core/material_repo.hpp"

class Scene
{
public:
    Scene();

    bool load(EntityComponentSystem& ecs, MaterialRepo& materials);
};

