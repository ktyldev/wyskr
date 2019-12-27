#pragma once

#include "component.h"

class Rotate : public Component
{
public:
    Rotate();

    bool initialise();
    void update();

private:
    Transform* transform_;
};
