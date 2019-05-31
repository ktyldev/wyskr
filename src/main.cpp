#include "stdio.h"
#include <string>
#include <fstream>

#include "glshader.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

SDL_Window*     window;
SDL_GLContext   context;

void createContext();
void compileShaders();

int main(int argc, char *argv[]) 
{
    printf("wyskr v0.0.1\n");

    createContext();
    compileShaders();

    // event loop
    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
                break;
        }

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

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    printf("%u\n", vertexBuffer);
}

void compileShaders()
{
    printf("compiling shaders...\n");
    GLuint program = LoadShader(
        "src/shaders/shader.vert", 
        "src/shaders/shader.frag");

    glUseProgram(program);
}
