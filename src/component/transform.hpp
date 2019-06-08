#include "ecs.hpp"
#include "math.hpp"

// TODO: differentiate between local/global positions
class Transform : public Component
{
public:
    Transform();
    Transform(Transform& other);
    Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

    bool initialise() { return true; }

    // METHODS
    // translates in local space
    void translate(float x, float y, float z);
    void rotate(float angle, glm::vec3 axis);
    void rotateEuler(float x, float y, float z);

    //
    // GETTERS
    //
    glm::vec3 position() const  { return position_; }
    glm::quat rotation() const  { return rotation_; }
    glm::vec3 scale() const     { return scale_; }

    // local transformation
    glm::mat4 local() const;

    //
    // SETTERS
    // 
    // all setters refer to local position
    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z, float w);
    void setScale(float x, float y, float z);

private:
    glm::vec3 position_;
    glm::quat rotation_;
    glm::vec3 scale_;
};
