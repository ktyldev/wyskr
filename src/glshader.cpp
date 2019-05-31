// based on https://badvertex.com/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c.html

#include "glshader.hpp"
#include "stdio.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

std::string readFile(const char* path)
{
    std::string content;
    std::ifstream stream(path, std::ios::in);

    if (!stream.is_open())
    {
        std::cerr << "could not read file " << path << ". file does not exist." << std::endl; 
        return "";
    }

    std::string line = "";
    while (!stream.eof())
    {
        std::getline(stream, line);
        content.append(line + "\n");
    }

    stream.close();
    return content;
}

GLuint LoadShader(const char* vertexPath, const char* fragmentPath)
{
    printf("reading shaders...\n");
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // read shaders
    std::string vertShaderStr = readFile(vertexPath);
    std::string fragShaderStr = readFile(fragmentPath);
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
