#pragma once

#include "core.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "testrenderer.hpp"

class Framework
{
public:
    Framework();
    Framework(unsigned int width, unsigned int height);
    ~Framework();

    int Run();

    bool Initialise();
    void Update();
    void Render();
    void Shutdown();

private:
    SDL_Window*     window_;
    SDL_GLContext   context_;
    unsigned int    width_;
    unsigned int    height_;

    // misc :)
    TestRenderer    renderer_;
    Colour          backgroundColour_;

    int MainLoop();
    void CreateContext();
    void ClearBackground();
};
