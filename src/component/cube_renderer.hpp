#include "renderer.hpp"

class CubeRenderer : public Renderer
{
public:
    CubeRenderer();
    CubeRenderer(Material& material);

    bool initialise();
    void update();
    void render(); 

    void setColour(Colour& colour);

protected:
    void createVertexBuffer();
    void createElementBuffer();

    void setShaderAttributes();
};
