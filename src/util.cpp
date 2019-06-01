#include "util.hpp"

#include "stdio.h"
#include <iostream>
#include <fstream>

std::string readFile(const char* path)
{
    std::string content;
    std::ifstream stream(path, std::ios::in);

    if (!stream.is_open())
    {
        std::cerr << "could not read file " << path << ". file does not exist." << std::endl; 
        return "";
    }

    std::string line = "";
    while (!stream.eof())
    {
        std::getline(stream, line);
        content.append(line + "\n");
    }

    stream.close();
    return content;
}
