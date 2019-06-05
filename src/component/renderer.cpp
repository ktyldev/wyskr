#include "renderer.hpp"

#include <iostream>
#include <vector>

#include "camera.hpp"

RendererComponent::RendererComponent(std::string vsPath, std::string fsPath) : 
    vsPath_(vsPath),
    fsPath_(fsPath)
{
}

bool RendererComponent::initialise()
{
    createVertexBuffer();
    createElementBuffer();

    compileShaders();
    setShaderAttributes();

    return true;
}

void RendererComponent::update()
{
}

void RendererComponent::render()
{
    updateView();
    updateProjection();
}

void RendererComponent::updateView()
{
    GLint uniView = glGetUniformLocation(shaderProgram_, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(Camera::main()->view()));
}

void RendererComponent::updateProjection()
{
    GLuint uniProjection = glGetUniformLocation(shaderProgram_, "projection");
    glUniformMatrix4fv(uniProjection, 1, GL_FALSE, glm::value_ptr(Camera::main()->projection()));
}

void RendererComponent::compileShaders()
{
    shaderProgram_ = loadShaders();

    // TODO: i get the feeling this will cause pain if i start using multiple vertex shaders
    glUseProgram(shaderProgram_);   
}

GLuint RendererComponent::loadShaders()
{
    printf("reading shaders...\n");
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // read shaders
    std::string vertShaderStr = readFile(vsPath_.c_str());
    std::string fragShaderStr = readFile(fsPath_.c_str());
    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // compile vertex shader
    printf("compiling vertex shader...\n");
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // check vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError(logLength > 1 ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
    if (logLength > 1)
    {
        std::cout << &vertShaderError[0] << std::endl;
    }

    // compile fragment shader
    printf("compiling fragment shader...\n");
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    // check fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError(logLength > 1 ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    if (logLength > 1)
    {
        std::cout << &fragShaderError[0] << std::endl;
    }

    printf("linking program...\n");
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError(logLength > 1 ? logLength : 1);
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    if (logLength > 1)
    {
        std::cout << &programError[0] << std::endl;
    }

    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}

