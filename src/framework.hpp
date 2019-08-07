#pragma once

#include "core/core.hpp"
#include "core/ecs.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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
    SDL_Window*             window_;
    SDL_GLContext           context_;
    EntityComponentSystem   ecs_;

    // misc :)
    Colour          backgroundColour_;

    int mainLoop();
    void createContext();
    void clearBackground();
    void displaySplash();
};
