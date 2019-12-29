#include "keyboard_input.hpp"

#include <iostream>

KeyboardInput::KeyboardInput() :
    quit_(0)
{
}

void KeyboardInput::update()
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                quit_ = 1;
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                handleEvent(&event.key);
                break;

            default:
                break;
        }
    }
}

bool KeyboardInput::quit()
{
    return quit_;
}

void KeyboardInput::printPressed()
{
    for (int i = 0; i < registered_.size(); ++i)
    {
        SDL_Keycode key = (SDL_Keycode)registered_[i];
        std::cout << SDL_GetKeyName(key) << ": ";
        std::cout << pressed_[i];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void KeyboardInput::printKey(SDL_KeyboardEvent* key)
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

void KeyboardInput::registerKey(SDL_Keycode key)
{
    std::string name = SDL_GetKeyName(key);
    int k = (int)key;

    for (auto& i : registered_)
    {
        if (k == i)
        {
            std::cout << "tried to register " << name << std::endl;
            std::cout << SDL_GetKeyName((SDL_Keycode)i) << " already registered" << std::endl;
            return;
        }
    }

    registered_.push_back(k);
    pressed_.push_back(false);

    std::cout << "registered key: " << name << std::endl;;
}

void KeyboardInput::handleEvent(SDL_KeyboardEvent* event)
{
    int k = (int)(event->keysym.sym);

    if (registeredIndex(k) == -1)
    {
        return;
    }

    for (int i = 0; i < registered_.size(); ++i)
    {
        if (registered_[i] == k)
        {
            if (event->type == SDL_KEYDOWN)
            {
                pressed_[i] = true;
            }
            else
            {
                pressed_[i] = false;
            }

            printPressed();
        }
    }
}

bool KeyboardInput::isPressed(SDL_Keycode key)
{
    int k = (int)key;

    for (int i = 0; i < registered_.size(); ++i)
    {
        if (registered_[i] == k)
        {
            return pressed_[i];
        }
    }

    return false;
}

int KeyboardInput::registeredIndex(int k)
{
    for (int i = 0; i < registered_.size(); ++i)
    {
        if (k == registered_[i])
        {
            return i;
        }
    }

    return -1;
}
