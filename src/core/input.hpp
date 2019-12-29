#pragma once

#include <SDL2/SDL.h>

class Input
{
public:
    Input();
    
    void update();

    bool quit();

private:
    bool quit_;

    void printKey(SDL_KeyboardEvent* key);
};
