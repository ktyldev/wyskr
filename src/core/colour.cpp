#include "colour.hpp"
#include <iostream>

Colour::Colour()
{
    set(0, 0, 0);
}

Colour::Colour(Colour& c)
{
    set(c.r(), c.g(), c.b());
}

Colour::Colour(float r, float g, float b)
{
    set(r, g, b);
}

void Colour::set(float r, float g, float b)
{
    v_.x = r;
    v_.y = g;
    v_.z = b;
}

void Colour::print()
{
    std::cout 
        << "(" << r() << ", " << g() << ", " << b() << ")" 
        << std::endl;
}

glm::vec3 Colour::vec3()
{
    return v_;
}
