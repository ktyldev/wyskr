#include "stdio.h"
#include <string>
#include <fstream>
#include <chrono>

#include "glshader.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

SDL_Window*     window;
SDL_GLContext   context;

GLuint shaderProgram;

void createContext();
void compileShaders();
void setShaderAttributes();
void createVertexBuffer();

int main(int argc, char *argv[]) 
{
    printf("wyskr v0.0.1\n");

    createContext();
    createVertexBuffer();

    compileShaders();
    setShaderAttributes();

    // event loop
    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
                break;
        }

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    // clean up
    SDL_GL_DeleteContext(context);
    SDL_Quit();

    return 0;
}

void createContext()
{
    // load SDL modules
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window = SDL_CreateWindow(
        "wyskr", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        800, 
        600, 
        SDL_WINDOW_OPENGL);

    context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();
}

void createVertexBuffer()
{
    // vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    GLfloat vertices[] = 
    {
         0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // red
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // green   
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // blue
    };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void setShaderAttributes()
{
    int stride = 5 * sizeof(float);
    // get reference to 'position' input of vertex shader
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(
        posAttrib, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        stride, 
        0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "colour");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(
        colAttrib,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(2 * sizeof(float))); // offset red position
}

void compileShaders()
{
    printf("compiling shaders...\n");
    shaderProgram = LoadShader(
        "src/shaders/shader.vert", 
        "src/shaders/shader.frag");

    glUseProgram(shaderProgram);
}

