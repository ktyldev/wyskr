#pragma once

#include "core/core.hpp"
#include "core/ecs.hpp"
#include "core/scene.hpp"
#include "core/material_repo.hpp"
#include "core/keyboard_input.hpp"

#include "component.h"

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

    const MaterialRepo&             materials() const;
    const EntityComponentSystem&    entities() const;

    KeyboardInput&            input();

private:
    // window
    SDL_Window*             window_;
    SDL_GLContext           context_;

    // misc :)
    KeyboardInput           input_;
    MaterialRepo            materials_;
    Scene                   scene_;
    EntityComponentSystem   ecs_;
    Colour                  backgroundColour_;

    // methods
    int mainLoop();
    void createContext();
    void clearBackground();
    void displaySplash();
};
