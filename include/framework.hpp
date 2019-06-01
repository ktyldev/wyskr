#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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

    unsigned int width_;
    unsigned int height_;

    int MainLoop();
    void CreateContext();
};
