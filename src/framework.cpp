#include "framework.hpp"
#include "component/transform.hpp"
#include "component/cuberenderer.hpp"

// TODO: move these to opengl context
#define DEFAULT_WIDTH   800
#define DEFAULT_HEIGHT  600
#define FIELD_OF_VIEW   110

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

    return success;
}

const MaterialRepo& Framework::materials() const 
{
    return materials_;
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

    // clean up
    SDL_GL_DeleteContext(context_);
    SDL_Quit();

    return 0;
}

bool Framework::initialise()
{
    // register materials
    materials_.registerMaterial("green", "res/shader/shader.vert", "res/shader/shader.frag");
    Colour green(0.0f, 1.0f, 0.0f);
    materials_.getMaterial("green").setColour(green);

    std::cout << "made green material: ";
    materials_.getMaterial("green").getColour().print();

    materials_.registerMaterial("red", "res/shader/shader.vert", "res/shader/shader.frag");
    Colour red(1.0f, 0.0f, 0.0f);
    materials_.getMaterial("red").setColour(red);

    std::cout << "made red material: ";
    materials_.getMaterial("red").getColour().print();

    createContext();
    
    if (!scene_.load(ecs_, materials_))
    {
        std::cout << "scene failed to load" << std::endl;
        return false;
    }

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
