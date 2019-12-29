#include "input.hpp"

#include <iostream>

Input::Input() :
    quit_(false)
{
}

void Input::update()
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                quit_ = true;
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                printKey(&event.key); 
                break;

            default:
                break;
        }
    }
}

bool Input::quit()
{
    return quit_;
}

void Input::printKey(SDL_KeyboardEvent* key)
{
    if (key->type == SDL_KEYDOWN)
    {
        std::cout << "pressed: ";
    }
    else 
    {
        std::cout << "released: ";
    }

    std::cout << SDL_GetKeyName(key->keysym.sym) << std::endl;
}
