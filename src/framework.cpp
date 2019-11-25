#include "framework.hpp"
#include "component/transform.hpp"
#include "component/cuberenderer.hpp"
#include "component/light.h"

// TODO: move these to opengl context
#define DEFAULT_WIDTH   800
#define DEFAULT_HEIGHT  600
#define FIELD_OF_VIEW   90

Framework::Framework() : Framework(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
}

Framework::Framework(unsigned int width, unsigned int height)
{
    Screen::initialise(width, height);
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

    success = mainLoop();

    shutdown();

    return success;
}

int Framework::mainLoop()
{
    // init context
    Time::start();
    // TODO: move SDL stuff to opengl context
    // event loop
    SDL_Event windowEvent;

    // go!
    while (true)
    {
        Time::update();

        // update context
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
                break;
        }
        update();

        // render context
        render();
    }

    return 0;
}

bool Framework::initialise()
{
    glFlush();
    createContext();
    
    // TODO: scene serialization
    // create entities
    auto& e1 = ecs_.addEntity("test1");
    auto& e2 = ecs_.addEntity("test2");

    // setup ambient light
    Colour ambientColour(0.1f, 0.1f, 0.1f);
    AmbientLight ambient(ambientColour);

    Colour c1(1.0f, 0.0f, 0.0f);
    e1.addComponent<Transform>();
    e1.getComponent<Transform>().translate(0.75f, 0.0f, 0.0f);
    CubeRenderer& cube(e1.addComponent<CubeRenderer>());
    cube.setColour(c1);
    cube.registerAmbientLight(ambient);

    Colour c2(0.0f, 0.0f, 1.0f);
    e2.addComponent<Transform>();
    e2.getComponent<Transform>().translate(-0.75f, 0.0f, 0.0f);
    CubeRenderer& cube2(e2.addComponent<CubeRenderer>());
    cube2.setColour(c2);
    cube2.registerAmbientLight(ambient);

    //e2.setParent(e1.shared_from_this());

    return ecs_.initialise();
}

void Framework::update()
{
    ecs_.update();
}

void Framework::render()
{
    clearBackground();

    ecs_.render();

    SDL_GL_SwapWindow(window_);
}

void Framework::shutdown()
{
    std::cout << "cleaning up..." << std::endl;

    // clear graphics memory
    glFlush();    

    // clean up
    SDL_GL_DeleteContext(context_);
    SDL_Quit();
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
