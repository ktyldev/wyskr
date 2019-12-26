#include "core/time.hpp"

#include "camera_orbit.hpp"

CameraOrbit::CameraOrbit() :
    transform_(nullptr)
{
}

bool CameraOrbit::initialise()
{
    transform_ = &(entity()->getComponent<Transform>());

    return transform_ != nullptr;
}

void CameraOrbit::update()
{
    double time = Time::time();
    
    float distance = 5.0f;

    glm::vec3 pos(cos(time) * distance, 2.0f, sin(time) * distance);

    transform_->setPosition(pos);
}
