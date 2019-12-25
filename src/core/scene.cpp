#include "core/scene.hpp"

#include "component/transform.hpp"
#include "component/cuberenderer.hpp"

Scene::Scene() 
{
}

bool Scene::load(EntityComponentSystem& ecs, MaterialRepo& materials) 
{
    struct CubeData
    {
        std::string name;
        std::string materialName;
        glm::vec3   offset;
    };

    std::vector<CubeData> cubes; 

    cubes.push_back({ "green_cube", "green",    glm::vec3(0.5f, 0.0f, -0.75f) });
    cubes.push_back({ "red_cube",    "red",     glm::vec3(-0.75f, 0.0f, 0.5f) });

    for (int i = 0; i < (int)cubes.size(); ++i)
    {
        // create entity
        auto& entity = ecs.addEntity(cubes[i].name);

        // add components
        auto& transform = entity.addComponent<Transform>();
        auto& renderer = entity.addComponent<CubeRenderer>();

        std::string matName = cubes[i].materialName;
        if (!materials.hasMaterial(matName))
        {
            std::cout << "could not locate material: " << matName << std::endl;
            continue;
        }
        Material& material = materials.getMaterial(matName);

        std::cout << "created material ";
        material.getColour().print();

        renderer.setMaterial(material);
        transform.translate(cubes[i].offset);
    }

    return true;
}

