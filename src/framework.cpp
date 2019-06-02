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

bool Framework::Initialise()
{
    CreateContext();

    Colour c(1.0f, 0.0f, 0.0f);
    renderer_.SetColour(c);
    bool success = renderer_.Initialise();

    return success;
}

void Framework::Render()
{
    ClearBackground();

    renderer_.Render();

    SDL_GL_SwapWindow(window_);
}

void Framework::ClearBackground()
{
    Colour c = backgroundColour_;
    glClearColor(c.r(), c.g(), c.b(), 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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
        DEFAULT_WIDTH, 
        DEFAULT_HEIGHT, 
        SDL_WINDOW_OPENGL);

    context_ = SDL_GL_CreateContext(window_);

    glewExperimental = GL_TRUE;
    glewInit();
}

