#pragma once

#include "core/core.hpp"
#include "core/ecs.hpp"

#include "component/transform.hpp"

class Camera : public Component
{
public:
    Camera();
    Camera(float fov, float near, float far);

    static Camera* main();

    virtual bool initialise();
    virtual void update();
    virtual void render();

    void setLookTarget(glm::vec3 target);

    glm::mat4 view();
    glm::mat4 projection();

private:
    float       fov_;
    float       near_;
    float       far_;

    glm::vec3   target_;
    glm::vec3   up_;

    Transform*  transform_;
};
