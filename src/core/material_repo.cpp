#include "core/material_repo.hpp"

MaterialRepo::MaterialRepo() {}

bool MaterialRepo::registerMaterial(
        std::string name,
        std::string vsPath,
        std::string fsPath)
{
    Material material(name, vsPath, fsPath);
    materials_.push_back(material);

    return true;
}

bool MaterialRepo::hasMaterial(std::string name)
{
    for (auto&& material : materials_)
    {
        if (material.getName() == name)
        {
            return true;
        }
    }

    return false;
}

Material& MaterialRepo::getMaterial(std::string name)
{
    for (auto&& material : materials_)
    {
        // TODO: string comparison bad
        if (material.getName() == name)
        {
            return material;
        }
    }

    // error if execution reaches this stage
    throw "could not find material " + name;
}
