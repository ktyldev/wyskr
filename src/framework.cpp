#define GLEW_STATIC
#include <GL/glew.h>

#include "framework.hpp"

#include "stdio.h"
#include <string>
#include <fstream>
#include <chrono>

#include "glshader.hpp"
#include "vertex.hpp"

// TODO: factor these out to renderer
GLuint shaderProgram;

void compileShaders();
void setShaderAttributes();

void createVertexBuffer();
void createElementBuffer();

#define DEFAULT_WIDTH   800
#define DEFAULT_HEIGHT  600

Framework framework_;

Framework::Framework() : Framework(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
}

Framework::Framework(unsigned int width, unsigned int height) :
    width_(width),
    height_(height)
{
    framework_ = *this; 
    printf("wyskr v0.0.1\n");
}

Framework::~Framework() 
{
}

int main(int argc, char *argv[]) 
{
    framework_.Run();
}

int Framework::Run()
{
    bool success = Initialise();

    // TODO: factor these out to renderer
    createVertexBuffer();
    createElementBuffer();
    compileShaders();
    setShaderAttributes();

    if (!success)
        return -1;

    return MainLoop();
}

int Framework::MainLoop()
{
    // event loop
    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
                break;
        }

        Render();
    }

    // clean up
    SDL_GL_DeleteContext(context_);
    SDL_Quit();

    return 0;
}

void Framework::Render()
{
    // TODO: set background colour in a better way
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 6);

    SDL_GL_SwapWindow(window_);
}

bool Framework::Initialise()
{
    CreateContext();

    return true;
}

void Framework::CreateContext()
{
    // load SDL modules
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window_ = SDL_CreateWindow(
        "wyskr", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        800, 
        600, 
        SDL_WINDOW_OPENGL);

    context_ = SDL_GL_CreateContext(window_);

    glewExperimental = GL_TRUE;
    glewInit();
}

void createVertexBuffer()
{
    VertexColour vertices[] = 
    {
    //              x       y               colour
        { glm::vec2(-0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f) }, // top left
        { glm::vec2( 0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f) }, // top right   
        { glm::vec2( 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f) }, // bottom right
        { glm::vec2(-0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // bottom left  
    };

    // vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void createElementBuffer()
{
    GLuint elements[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    // element buffer object
    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
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

