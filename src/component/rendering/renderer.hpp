#include <string>

#include "core/core.hpp"
#include "core/ecs.hpp"
#include "core/material.hpp"

class Renderer : public Component
{
public:
    Renderer();
    Renderer(Material& material);

    virtual bool initialise();
    virtual void update();
    virtual void render();

    void setMaterial(Material& material);

    Material& getMaterial();

protected:
    virtual void createVertexBuffer() = 0;
    virtual void createElementBuffer() = 0;

    GLuint shaderProgram() { return shaderProgram_; }

private:
    Material*       material_;

    std::string     vsPath_;
    std::string     fsPath_;
    GLuint          shaderProgram_;

    glm::mat4       view_;
    glm::mat4       projection_;

    void compileShaders();

    void updateView();
    void updateProjection();
};
