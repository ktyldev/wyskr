#include "screen.hpp"

int width_;
int height_;
float aspect_;

void Screen::initialise(unsigned int width, unsigned int height)
{
    width_ = width;
    height_ = height;
    aspect_ = (float)width / (float)height;
}

unsigned int Screen::width()
{
    return width_;
}

unsigned int Screen::height()
{
    return height_;
}

float Screen::aspect()
{
    return aspect_;
}
