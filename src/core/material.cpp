#include <iostream>

#include "core/material.hpp"

Material::Material(
    const std::string name, 
    const std::string vsPath,
    const std::string fsPath) :
    name_(name),
    vsPath_(vsPath),
    fsPath_(fsPath)
{
    colour_ = Colour(0,0,0);
}

Material::Material(const Material& other) :
    name_(other.getName()),
    vsPath_(other.getVsPath()),
    fsPath_(other.getFsPath()),
    colour_(other.getColour())
{
}

bool Material::initialise()
{
    // compile shaders
    std::cout << "compiling shaders for material " << name_ << std::endl;
    GLuint vert = compileShader(vsPath_, GL_VERTEX_SHADER);
    GLuint frag = compileShader(fsPath_, GL_FRAGMENT_SHADER);

    linkShaders(vert, frag);

    // clean up 
    glDeleteShader(vert);
    glDeleteShader(frag);

    return true;
}

void Material::setColour(Colour& colour)
{
    //std::cout << "setting colour from ";
    //colour.print();

    colour_ = colour;

    //std::cout << "to ";
    //colour_.print();
    //colour_.print();
}

const Colour& Material::getColour() const
{
    return colour_;
}

void Material::setShaderAttributes()
{
    int stride = sizeof(VertexColour);

    // position
    GLint pos = glGetAttribLocation(shaderProgram_, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, stride, 0);

    // normal
    GLint normal = glGetAttribLocation(shaderProgram_, "normal");
    glEnableVertexAttribArray(normal);
    glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

    // colour
    GLint colour = glGetAttribLocation(shaderProgram_, "colour");
    glEnableVertexAttribArray(colour);
    glVertexAttribPointer(colour, 3, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
}

GLuint Material::getShaderProgram()
{
    return shaderProgram_;
}

void Material::linkShaders(GLuint vert, GLuint frag)
{
    GLint result = GL_FALSE;
    int logLength;

    std::cout << "linking shader program" << std::endl;

    // create program, attach shaders
    shaderProgram_ = glCreateProgram();
    glAttachShader(shaderProgram_, vert);
    glAttachShader(shaderProgram_, frag);

    glLinkProgram(shaderProgram_);

    // check program health
    glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &result);
    glGetProgramiv(shaderProgram_, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> err(logLength > 1 ? logLength : 1);
    glGetProgramInfoLog(shaderProgram_, logLength, NULL, &err[0]);
    if (logLength > 1)
    {
        std::cout << &err[0] << std::endl;
    }

    // detach shaders from program (?)
    glDetachShader(shaderProgram_, vert);
    glDetachShader(shaderProgram_, frag);
}

GLuint Material::compileShader(std::string path, GLenum type)
{
    std::cout << "compiling shader " << path << std::endl;

    GLuint shader = glCreateShader(type);

    std::string str = readFile(path.c_str(), true).data();
    const char* src = str.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // compile
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    // check
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> err(logLength > 1 ? logLength : 1);
    glGetShaderInfoLog(shader, logLength, NULL, &err[0]);
    if (logLength > 1)
    {
        std::cout << &err[0] << std::endl;
    }

    return shader;
}

