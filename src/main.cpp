#include "stdio.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

int main(int argc, char *argv[]) 
{
    printf("hello, world!\n");

    // load SDL modules
    SDL_Init(SDL_INIT_VIDEO);

    //
    // create opengl context
    //
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    // stencil buffer
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_Window* window = SDL_CreateWindow(
            "wyskr", 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            800, 
            600, 
            SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);

    // event loop
    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
                break;
        }

        SDL_GL_SwapWindow(window);
    }

    // clean up
    SDL_GL_DeleteContext(context);
    SDL_Quit();

    return 0;
}
