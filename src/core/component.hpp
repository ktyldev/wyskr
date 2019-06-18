#pragma once

class Entity;

class Component
{
public:
    virtual bool initialise() = 0;
    virtual void update() {}
    virtual void render() {}

    virtual ~Component() {}

    void setEntity(Entity& entity)  { entity_ = &entity; }
    Entity* entity() const          { return entity_; }

private:
    Entity* entity_;
};
