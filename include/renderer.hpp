#include <string>

#include "core.hpp"

class Renderer
{
public:
    Renderer(std::string vsPath, std::string fsPath);

    virtual bool initialise();
    virtual void update();
    virtual void render();

protected:
    virtual void createVertexBuffer() = 0;
    virtual void createElementBuffer() = 0;
    virtual void setShaderAttributes() = 0;

    GLuint shaderProgram() { return shaderProgram_; }

private:
    std::string     vsPath_;
    std::string     fsPath_;
    GLuint          shaderProgram_;

    glm::mat4       view_;
    glm::mat4       projection_;

    GLuint loadShaders();
    void compileShaders();

    void updateView();
    void updateProjection();
};
