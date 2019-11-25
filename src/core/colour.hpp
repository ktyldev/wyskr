#pragma once

#include <glm/vec3.hpp>

class Colour
{
public:
    Colour();
    Colour(Colour& c);
    Colour(float r, float g, float b);

    void set(float r, float g, float b);
    glm::vec3 vec3();

    float r() { return v_.x; };
    float g() { return v_.y; };
    float b() { return v_.z; };

    void print();

private:
    glm::vec3 v_;
};
