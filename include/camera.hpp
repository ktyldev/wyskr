#include "core.hpp"

class Camera
{
public:
    Camera();
    Camera(float fov, float near, float far);

    static Camera* main();

    glm::mat4 view();
    glm::mat4 projection();

private:
    float fov_;
    float near_;
    float far_;

    glm::vec3 position_;
    glm::vec3 target_;
    glm::vec3 up_;
};
