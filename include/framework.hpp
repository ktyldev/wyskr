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

    static Framework* instance();

    int run();

    bool initialise();
    void update();
    void render();
    void shutdown();

private:
    // window
    SDL_Window*     window_;
    SDL_GLContext   context_;

    // misc :)
    TestRenderer    renderer_;
    Colour          backgroundColour_;

    int mainLoop();
    void createContext();
    void clearBackground();
};
