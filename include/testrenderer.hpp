#pragma once

#include "core.hpp"

#include <string>

class TestRenderer
{
public:
    TestRenderer();
    ~TestRenderer();

    bool Initialise();
    void Render();

    void SetColour(Colour& colour);

private:
    std::string     vsPath_;
    std::string     fsPath_;
    GLuint          shaderProgram_;
    glm::vec3       colour_;

    GLuint LoadShaders(const char* vertexPath, const char* fragmentPath);
    void CompileShaders();
    void SetShaderAttributes();
    void CreateVertexBuffer();
    void CreateElementBuffer();
};
