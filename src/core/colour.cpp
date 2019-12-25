#include <iostream>

#include "colour.hpp"

Colour::Colour()
{
    set(0, 0, 0);
}

Colour::Colour(Colour& c)
{
    set(c.r(), c.g(), c.b());
}

Colour::Colour(const Colour& c)
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

glm::vec3 Colour::vec3() const
{
    return v_;
}

void Colour::print() const
{
    std::cout << "(" << r() << ", " << g() << ", " << b() << ")" << std::endl;
}
