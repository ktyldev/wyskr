#pragma once

#include <SDL2/SDL.h>
#include <vector>


class KeyboardInput
{
public:
    KeyboardInput();

    void update();

    bool quit();

    // TODO: allow registration of external inputs
    void registerKey(SDL_Keycode key);
    bool isPressed(SDL_Keycode key);

private:
    int quit_;

    std::vector<int>    registered_;
    std::vector<bool>   pressed_;

    void printPressed();
    void printKey(SDL_KeyboardEvent* key);
    void handleEvent(SDL_KeyboardEvent* event);

    int registeredIndex(int k);
};
