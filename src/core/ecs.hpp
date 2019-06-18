#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include "core/component.hpp"
#include "core/entity.hpp"

class EntityComponentSystem
{
private:
    std::vector<std::unique_ptr<Entity>> entities_;
    
public:
    bool initialise() 
    {
        for (auto& e : entities_)
        {
            if (!e->initialise())
                return false;
        }

        return true;
    }
    void update() { for (auto& e : entities_) e->update(); }
    void render() { for (auto& e : entities_) e->render(); }

    void refresh()
    {
        entities_.erase(std::remove_if(std::begin(entities_), std::end(entities_),
            [](const std::unique_ptr<Entity> &entity)
            {
                return !entity->isActive(); 
            }),
            std::end(entities_)); 
    }

    Entity& addEntity()
    {
        Entity* e = new Entity();
        std::unique_ptr<Entity> uPtr{ e };
        entities_.emplace_back(std::move(uPtr));

        return *e;
    }
};
