#include <boost/program_options.hpp>

#include "framework.hpp"

#define DEFAULT_WIDTH   800
#define DEFAULT_HEIGHT  600
#define FIELD_OF_VIEW   90  

enum RenderMode
{
    curses,
    opengl
};

struct ProgramOptions
{
    RenderMode mode;
};

int readOptions(int c, char *v[], ProgramOptions &options)
{
    namespace po = boost::program_options;
    // https://www.boost.org/doc/libs/1_70_0/doc/html/program_options/tutorial.html
    po::options_description desc("allowed options");
    desc.add_options()
        ("help", "produce message help")
        ("curses", "run in curses mode")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(c, v, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }
    
    options.mode = vm.count("curses") 
        ? RenderMode::curses 
        : RenderMode::opengl;

    return 0;
}

int main(int argc, char *argv[]) 
{
    Framework framework;
    ProgramOptions options;
    if (readOptions(argc, argv, options) != 0)
        return 1;

    switch (options.mode)
    {
        case RenderMode::curses:
            std::cout << "TODO: implement curses rendering mode" << std::endl;
            break;

        case RenderMode::opengl:
            framework.run();
            std::cout << "done" << std::endl;
            break;
    }

    return 0;
}
