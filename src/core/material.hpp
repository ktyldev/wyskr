#pragma once

#include <string>

#include "core/core.hpp"

class Material
{
public:
    Material(const std::string name, const std::string vsPath, const std::string fsPath);
    Material(const Material& other);

    bool            initialise();

    // properties
    void            setColour(Colour& colour);
    const Colour&   getColour() const;

    void            setShaderAttributes();
    GLuint          getShaderProgram();

    std::string     getName()   const { return name_; }
    std::string     getVsPath() const { return vsPath_; }
    std::string     getFsPath() const { return fsPath_; }
    
private:
    std::string name_;
    std::string vsPath_;
    std::string fsPath_;
    
    GLuint      shaderProgram_;
    Colour      colour_;

    GLuint      compileShader(std::string path, GLenum type);
    void        linkShaders(GLuint vert, GLuint frag);
};
