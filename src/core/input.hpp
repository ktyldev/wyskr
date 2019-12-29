#pragma once

#include <SDL2/SDL.h>

class Input
{
public:
    Input();
    
    void update();

    bool quit();

private:
    bool        quit_;
};
