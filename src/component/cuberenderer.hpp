#include "renderer.hpp"
#include "light.h"

// TODO: factor out litrenderer
class CubeRenderer : public Renderer
{
public:
    CubeRenderer();
    CubeRenderer(std::string vsPath, std::string fsPath);

    bool initialise();
    void update();
    void render(); 

    void setColour(Colour& colour);

    void registerAmbientLight(AmbientLight& light);
    void registerDirectionalLight(DirectionalLight& light);

protected:
    void createVertexBuffer();
    void createElementBuffer();

    void setShaderAttributes();

    void updateLighting();

private:
    Colour colour_;

    std::vector<AmbientLight*> ambientLights_;
    std::vector<DirectionalLight*> directionalLights_;
};
