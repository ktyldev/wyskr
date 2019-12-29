#include "input.hpp"

Input::Input() :
    quit_(false)
{
}

void Input::update()
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit_ = true;
            return;
        }
    }
}

bool Input::quit()
{
    return quit_;
}
