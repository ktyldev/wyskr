#include "core/scene.hpp"

#include "component.h"

Scene::Scene() 
{
}

bool Scene::load(EntityComponentSystem& ecs, MaterialRepo& materials) 
{
    ecs_        = &ecs;
    materials_  = &materials;

    //addCube();
    addTree();
    addCamera();

    return true;
}

void Scene::addCube()
{
    auto& cubeRoot = ecs_->addEntity("cube_root");
    cubeRoot.addComponent<Transform>();
    cubeRoot.addComponent<Rotate>();

    auto& cube = ecs_->addEntity("cube");
    auto& transform = cube.addComponent<Transform>();
    auto& renderer = cube.addComponent<CubeRenderer>();
    cube.setParent(cubeRoot);

    std::cout << ecs_->getParent(cube)->node()->name() << std::endl;

    Material& material = materials_->getMaterial("green");
    renderer.setMaterial(material);
}

void Scene::addTree()
{
    struct CubeData
    {
        std::string name;
        std::string materialName;
        glm::vec3   offset;
    };

    std::vector<CubeData> cubes; 

    float yBase = -2.0f;
    float z = 0.0f;
    
    auto& tree = ecs_->addEntity("tree");
    auto& treeTransform = tree.addComponent<Transform>();
    tree.addComponent<RotationInput>();

    treeTransform.setScale(1, 1, 1);

    cubes.push_back({ "cube_green_2_0", "green", glm::vec3(     0, yBase + 3, z) });

    cubes.push_back({ "cube_green_1_0", "green", glm::vec3( -0.5f, yBase + 2, z) });
    cubes.push_back({ "cube_green_1_1", "green", glm::vec3(  0.5f, yBase + 2, z) });

    cubes.push_back({ "cube_green_0_0", "green", glm::vec3(  1.0f, yBase + 1, z) });
    cubes.push_back({ "cube_green_0_1", "green", glm::vec3(  0.0f, yBase + 1, z) });
    cubes.push_back({ "cube_green_0_2", "green", glm::vec3( -1.0f, yBase + 1, z) });

    cubes.push_back({ "cube_red",   "red",      glm::vec3(0, yBase, z) });

    for (int i = 0; i < (int)cubes.size(); ++i)
    {
        // create entity
        auto& entity = ecs_->addEntity(cubes[i].name);

        entity.setParent(tree);

        // add components
        auto& transform = entity.addComponent<Transform>();
        auto& renderer = entity.addComponent<CubeRenderer>();

        float scale = 0.9f;
        transform.setScale(scale, scale, scale);

        std::string matName = cubes[i].materialName;
        if (!materials_->hasMaterial(matName))
        {
            std::cout << "could not locate material: " << matName << std::endl;
            continue;
        }
        Material& material = materials_->getMaterial(matName);

        //std::cout << "created material ";
        //material.getColour().print();

        renderer.setMaterial(material);
        transform.translate(cubes[i].offset);
    }
}

void Scene::addCamera()
{
    glm::vec3 startPos(1, 1, 4);
    glm::vec3 target(0, 0, 0);

    // create entity
    auto&entity = ecs_->addEntity("camera");

    // add components
    auto& transform = entity.addComponent<Transform>();
    auto& camera = entity.addComponent<Camera>();
    //entity.addComponent<CameraOrbit>();

    transform.translate(startPos);
}
