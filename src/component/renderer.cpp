#include <iostream>
#include <vector>

#include "camera.hpp"
#include "component/renderer.hpp"

Renderer::Renderer() :
    material_(nullptr)
{
}

Renderer::Renderer(Material& material) 
{
    material_ = &material;
}

bool Renderer::initialise()
{
    // TODO: materials should be initialised by material repo, not
    // by individual renderer components
    bool success = material_->initialise();
    if (success)
    {
        shaderProgram_ = material_->getShaderProgram();

        // TODO: i get the feeling this will cause pain if i start 
        // using multiple vertex shaders
        glUseProgram(shaderProgram_);   
    }

    return success;
}

void Renderer::update()
{
}

void Renderer::render()
{
    if (material_ == nullptr)
    {
        std::cout << "renderer error: no material set" << std::endl;
        return;
    }

    updateView();
    updateProjection();

    createVertexBuffer();
    createElementBuffer();

    material_->setShaderAttributes();
}

void Renderer::setMaterial(Material& material)
{
    material_ = &material;
    //material.getColour().print();
    //std::cout << "set material " << material_->getName() << " colour: ";
    //material_->getColour().print();
}

Material& Renderer::getMaterial()
{
    return *material_;
}

void Renderer::updateView()
{
    GLint uniView = glGetUniformLocation(shaderProgram_, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(Camera::main()->view()));
}

void Renderer::updateProjection()
{
    GLuint uniProjection = glGetUniformLocation(shaderProgram_, "projection");
    glUniformMatrix4fv(uniProjection, 1, GL_FALSE, glm::value_ptr(Camera::main()->projection()));
}


