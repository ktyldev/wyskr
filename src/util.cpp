#include "util.hpp"

#include <stdio.h>
#include <iostream>
#include <fstream>

std::vector<char> readFile(const std::string& filename, bool appendNewline)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
        throw std::runtime_error("failed to open file");

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize + (appendNewline ? 1 : 0));
    
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    if (appendNewline)
    {
        buffer.insert(buffer.end() - 1, '\n');  
    }

    return buffer;
}
