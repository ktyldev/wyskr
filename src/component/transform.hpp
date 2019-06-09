#include "core/ecs.hpp"
#include "core/math.hpp"

// TODO: differentiate between local/global positions
class Transform : public Component
{
public:
    Transform();
    Transform(Transform& other);
    Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

    bool initialise() { return true; }
    void update();

    // METHODS
    // translates in local space
    void translate(float x, float y, float z);
    void rotate(float angle, glm::vec3 axis);

    //
    // GETTERS
    //
    glm::vec3 position() const  { return position_; }
    glm::quat rotation() const  { return rotation_; }
    glm::vec3 scale() const     { return scale_; }

    // local transformation
    glm::mat4 local() const     { return local_; }

    //
    // SETTERS
    // 
    // all setters refer to local position
    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z, float w);
    void setScale(float x, float y, float z);

private:
    glm::mat4 local_;

    // local transformations
    glm::vec3 position_;
    glm::quat rotation_;
    glm::vec3 scale_;

    void updateLocal();
};
