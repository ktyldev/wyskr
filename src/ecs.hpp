#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentTypeId = std::size_t;

inline ComponentTypeId getComponentTypeId()
{
    static ComponentTypeId lastId = 0;
    return lastId++;
}

template <typename T> inline ComponentTypeId getComponentTypeId() noexcept
{
    static ComponentTypeId typeId = getComponentTypeId();
    return typeId;
}

// maximum amount of compoents an entity is able to hold
constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
    virtual bool initialise() = 0;
    virtual void update() {}
    virtual void render() {}

    virtual ~Component() {}

    void setEntity(Entity& entity) { entity_ = &entity; }
    Entity* entity() const { return entity_; }
private:
    Entity* entity_;
};

class Entity
{
public:
    bool initialise() 
    {
        for (auto& c : components_)
        {
            if (!c->initialise())
                return false;
        }

        return true;
    }
    void update() { for(auto& c : components_) c->update(); }
    void render() { for(auto& c : components_) c->render(); }

    bool isActive() { return active_; }
    void destroy()  { active_ = false; }

    template <typename T> 
    bool hasComponent() const
    {
        return componentBitSet_[getComponentTypeId<T>];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... args)
    {
        T* c(new T(std::forward<TArgs>(args)...)); 
        c->setEntity(*this);
        std::unique_ptr<Component> uPtr{ c };        
        components_.emplace_back(std::move(uPtr));

        componentArray_[getComponentTypeId<T>()] = c;
        componentBitSet_[getComponentTypeId<T>()] = true;

        return *c;
    }

    template <typename T>
    T& getComponent() const
    {
        auto ptr(componentArray_[getComponentTypeId<T>()]);
        return *static_cast<T*>(ptr);
    }

private:
    bool active_ = true;
    std::vector<std::unique_ptr<Component>> components_;

    ComponentArray  componentArray_;
    ComponentBitSet componentBitSet_;
};

class ECSManager
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
