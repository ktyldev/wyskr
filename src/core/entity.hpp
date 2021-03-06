// entity is fully implemented in the header file until i can figure out
// how to move those pesky template functions into an implementor

// TODO: implement copy constructor

#pragma once

#include <memory>
#include <vector>
#include <bitset>

#include "core/node.hpp"
#include "core/component_type.hpp"
#include "core/component.hpp"

class Component;

typedef std::shared_ptr<Entity> EntityPtr;

// maximum number of components an entity is able to hold
constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Entity
{
public:
    Entity(std::string name)
    {
        node_ = Node::create(name);
    }

    bool initialise()
    {
        for (auto& c : components_)
        {
            if (!c->initialise())
                return false;
        }

        return true;
    }

    NodePtr node() { return std::shared_ptr<Node>(node_); }


    void setParent(Entity& entity) { node_->setParent(entity.node()); }

    void update() { for (auto& c : components_) { c->update(); } }
    void render() { for (auto& c : components_) { c->render(); } }

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
        // instantiate component with args...
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
    NodePtr node_;

    bool active_ = true;
    std::vector<std::unique_ptr<Component>> components_;

    ComponentBitSet componentBitSet_;
    ComponentArray  componentArray_;
};
