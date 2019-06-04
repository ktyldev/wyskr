#include "renderercomponent.hpp"

class CubeRendererComponent : public RendererComponent
{
public:
    CubeRendererComponent();
    CubeRendererComponent(std::string vsPath, std::string fsPath);

    bool initialise();
    void update();
    void render(); 

    void setColour(Colour& colour);

protected:
    void createVertexBuffer();
    void createElementBuffer();

    void setShaderAttributes();

private:
    glm::vec3 colour_;
};
