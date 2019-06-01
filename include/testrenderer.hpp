#pragma once

#include "core.hpp"

#include <string>

class TestRenderer
{
public:
    TestRenderer();
    ~TestRenderer();

    bool Initialise();

private:
    std::string     vsPath_;
    std::string     fsPath_;
    GLuint          shaderProgram_;

    GLuint LoadShaders(const char* vertexPath, const char* fragmentPath);
    void CompileShaders();
    void SetShaderAttributes();
    void CreateVertexBuffer();
    void CreateElementBuffer();
};
