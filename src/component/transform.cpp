#include "component/transform.hpp"

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

void Transform::update()
{
    updateLocal();    
}

void Transform::updateLocal()
{
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position_);
    glm::mat4 rotation = glm::mat4_cast(rotation_);
    glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale_);

    local_ = scaling * rotation * translation;
}

void Transform::translate(float x, float y, float z) 
{
    position_.x += x;
    position_.y += y;
    position_.z += z;
}

void Transform::rotate(float angle, glm::vec3 axis)
{
    rotation_ = glm::rotate(rotation_, angle, axis);
}

void Transform::rotateEuler(float x, float y, float z)
{

    glm::quat rot(glm::vec3(x, y, z));
    std::cout << 
        rot.x << " " <<
        rot.y << " " <<
        rot.z << " " <<
        rot.w << " " <<
        std::endl;

    rotation_ = rot * rotation_;

    std::cout << 
        rotation_.x << " " <<
        rotation_.y << " " <<
        rotation_.z << " " <<
        rotation_.w << " " <<
        std::endl;
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
