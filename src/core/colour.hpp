#pragma once

#include <iostream>

#include <glm/vec3.hpp>

class Colour
{
public:
    static const Colour black;
    static const Colour white;
    static const Colour red;     
    static const Colour green;  
    static const Colour blue;    

    Colour();
    Colour(Colour& c);
    Colour(const Colour& c);
    Colour(float r, float g, float b);

    void set(float r, float g, float b);
    glm::vec3 vec3() const;

    float r() const { return v_.x; };
    float g() const { return v_.y; };
    float b() const { return v_.z; };

    void print() const;

private:
    glm::vec3 v_;
};
