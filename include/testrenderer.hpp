#pragma once

#include "core.hpp"

#include <string>
#include <chrono>

class TestRenderer
{
public:
    TestRenderer();
    ~TestRenderer();

    bool initialise();
    void update();
    void render();

    void setColour(Colour& colour);

private:
    std::string     vsPath_;
    std::string     fsPath_;
    GLuint          shaderProgram_;
    glm::vec3       colour_;

    GLuint loadShaders(const char* vertexPath, const char* fragmentPath);
    void compileShaders();
    void setShaderAttributes();
    void createVertexBuffer();
    void createElementBuffer();
};
