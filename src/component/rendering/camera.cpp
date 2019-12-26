#include "camera.hpp"

#define FOV     60.0f
// clipping planes
#define NEAR    1.0f
#define FAR     10.f

Camera* main_;

Camera::Camera() : Camera(FOV, NEAR, FAR)
{
}

Camera::Camera(float fov, float near, float far) :
    fov_(fov),
    near_(near),
    far_(far)
{
    if (main_ != nullptr)
    {
        throw "tried to re-assign singleton";
    }
    main_ = this;

    //position_   = glm::vec3(1.2f, 1.2f, 1.2f);
    target_     = glm::vec3(0.0f, 0.0f, 0.0f);
    up_         = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera* Camera::main()
{
    return main_;
}

bool Camera::initialise()
{
    transform_ = &(entity()->getComponent<Transform>());

    return true;
}

void Camera::update()
{
}

void Camera::render()
{
}

glm::mat4 Camera::view()
{
    if (transform_ == nullptr)
    {
        std::cout << "camera transform is null" << std::endl;
    }

    return glm::lookAt(transform_->position(), target_, up_); 
}

glm::mat4 Camera::projection()
{
    return glm::perspective(
        glm::radians(FOV),
        Screen::aspect(),
        near_,
        far_);
}
