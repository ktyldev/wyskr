#include "main.hpp"

#include "stdio.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>

#include "core/ecs.hpp"
#include "component/cuberenderer.hpp"
#include "component/transform.hpp"

#define DEFAULT_WIDTH   800
#define DEFAULT_HEIGHT  600
#define FIELD_OF_VIEW   90  

Framework               framework;
EntityComponentSystem   ecs;

auto& testEntity(ecs.addEntity());

int main(int argc, char *argv[]) 
{
    framework.run();
}

Framework::Framework() : Framework(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
}

Framework::Framework(unsigned int width, unsigned int height)
{
    Screen::initialise(width, height);
    framework = *this; 
}

Framework::~Framework() 
{
}

int Framework::run()
{
    displaySplash();

    bool success = initialise();

    if (!success)
        return -1;

    return mainLoop();
}

int Framework::mainLoop()
{
    Time::start();

    // event loop
    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
                break;
        }

        Time::update();

        update();
        render();
    }

    // clean up
    SDL_GL_DeleteContext(context_);
    SDL_Quit();

    return 0;
}

bool Framework::initialise()
{
    createContext();

    Colour c(1.0f, 0.0f, 0.0f);
    testEntity.addComponent<Transform>();
    testEntity.addComponent<CubeRenderer>();
    testEntity.getComponent<CubeRenderer>().setColour(c);

    return ecs.initialise();
}

void Framework::update()
{
    ecs.update();
}

void Framework::render()
{
    clearBackground();

    ecs.render();

    SDL_GL_SwapWindow(window_);
}

void Framework::clearBackground()
{
    Colour c = backgroundColour_;
    glClearColor(c.r(), c.g(), c.b(), 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framework::createContext()
{
    // load SDL modules
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window_ = SDL_CreateWindow(
        "wyskr", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        DEFAULT_WIDTH, 
        DEFAULT_HEIGHT, 
        SDL_WINDOW_OPENGL);

    context_ = SDL_GL_CreateContext(window_);

    glewExperimental = GL_TRUE;
    glewInit();
}

void Framework::displaySplash()
{
    std::string versionTemplate("{version}");
    std::string version("0.0.1");
    std::vector<char> splash(readFile("res/splash.txt"));
    std::string splashStr(splash.begin(), splash.end());

    size_t i = splashStr.find(versionTemplate);

    if (i != std::string::npos)
    {
        splashStr.replace(i, versionTemplate.length(), version);
    }
    else 
    {
        throw "D:";
    }

    std::cout << splashStr << std::endl;
}
