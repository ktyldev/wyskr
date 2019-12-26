#pragma once

#include <string>

#include "core/material.hpp"

class MaterialRepo
{
public:
    MaterialRepo();

    bool registerMaterial(std::string name, std::string vsPath, std::string fsPath);

    bool hasMaterial(std::string name);
    Material& getMaterial(std::string name);

private:
    std::vector<Material> materials_;
};
