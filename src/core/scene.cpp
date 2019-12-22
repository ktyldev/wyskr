#include "core/scene.hpp"

#include "component/transform.hpp"
#include "component/cuberenderer.hpp"

Scene::Scene() 
{
}

bool Scene::load(EntityComponentSystem& ecs) 
{
    struct CubeData
    {
        std::string name;
        Colour&     colour;
        glm::vec3   offset;
    };
    Colour red(1.0f, 0.0f, 0.0f);
    Colour blue(0.0f, 0.0f, 1.0f);

    std::vector<CubeData> cubes; 
    cubes.push_back({ "red_cube",   red,    glm::vec3(0.75f, 0.0f, -0.5f) });
    cubes.push_back({ "blue_cube",  blue,   glm::vec3(-0.75f, 0.0f, 0.5f) });

    for (int i = 0; i < (int)cubes.size(); ++i)
    {
        // create entity
        auto& entity = ecs.addEntity(cubes[i].name);

        // add components
        auto& transform = entity.addComponent<Transform>();
        auto& renderer = entity.addComponent<CubeRenderer>();

        renderer.setColour(cubes[i].colour);
        transform.translate(cubes[i].offset);
    }

    return true;
}

