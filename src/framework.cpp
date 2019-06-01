#include "core.hpp"

#include "framework.hpp"

#include "stdio.h"
#include <string>
#include <fstream>
#include <chrono>

#define DEFAULT_WIDTH   800
#define DEFAULT_HEIGHT  600

Framework       framework_;
TestRenderer    renderer_;

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

    bool success = renderer_.Initialise();
    return success;
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

