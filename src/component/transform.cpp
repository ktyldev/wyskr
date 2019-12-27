#include "transform.hpp"

#include "framework.hpp"

#include <stdio.h>
#include <iostream>

Transform::Transform() : Transform(
    glm::vec3(0, 0, 0),
    glm::quat(0, 0, 0, 1),
    glm::vec3(1, 1, 1))
{
}

Transform::Transform(Transform& other) : Transform(
    other.position(),
    other.rotation(),
    other.scale())
{
}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale) :
    position_(position),
    rotation_(rotation),
    scale_(scale)
{
}

// update world transformation
void Transform::update()
{
    // to get the current world transformation traverse up the
    // roots of each parent and combine each tranform's local
    // transformation

    updateLocal();

    glm::mat4 world = local_;
    
    const EntityComponentSystem& ecs = Framework::instance()->entities();

    //std::cout << "start transform update" << std::endl;
    
    bool done = false;
    Entity* current = entity();
    Entity* parent = nullptr;
    int depth = 0;
    int maxDepth = 5;

    while (!done)
    {
        parent = ecs.getParent(*current);
        if (parent == nullptr)
        {
            //std::cout << "reached root node, exit recursive graph traversal" << std::endl;
            done = true;
            break;
        }

        depth++;
        if (depth > maxDepth)
        {
            std::cout << "hit max depth, exiting to avoid crash" << std::endl;
            done = true;
            break;
        }

        world = parent->getComponent<Transform>().local() * world;

        current = parent;
    }

    //std::cout << "end transform update" << std::endl;

    world_ = world;
}

void Transform::updateLocal()
{
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position_);
    glm::mat4 rotation = glm::mat4_cast(rotation_);
    glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale_);

    local_ = translation * rotation * scaling;
}

void Transform::translate(float x, float y, float z) 
{
    translate(glm::vec3(x, y, z));
}

void Transform::translate(glm::vec3 translation)
{
    position_ += translation;
}

void Transform::rotate(float angle, glm::vec3 axis)
{
    rotation_ = glm::rotate(rotation_, angle, axis);
}

void Transform::setPosition(glm::vec3 position)
{
    position_ = position;
}

void Transform::setPosition(float x, float y, float z)
{
    position_.x = x;
    position_.y = y;
    position_.z = z;
}

void Transform::setScale(float x, float y, float z)
{
    scale_.x = x;
    scale_.y = y;
    scale_.z = z;
}
