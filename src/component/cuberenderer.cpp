#include "component/cuberenderer.hpp"
#include "component/transform.hpp"

CubeRenderer::CubeRenderer() :
    Renderer()
{
}

CubeRenderer::CubeRenderer(Material& material) :
    Renderer(material)
{
}

bool CubeRenderer::initialise()
{
    return Renderer::initialise();
}

void CubeRenderer::update()
{
    Renderer::update();
}

void CubeRenderer::render()
{
    // lighting

    // ambient
    glm::vec3 ambientColour = glm::vec3(0.1f, 0.1f, 0.1f);
    GLint uniAmbient = glGetUniformLocation(shaderProgram(), "ambient");
    glUniform3fv(uniAmbient, 1, glm::value_ptr(ambientColour));

    // directional
    glm::vec3 lightVector = glm::vec3(-0.8f, 0.2f, 0.2f);
    GLint uniLightVector = glGetUniformLocation(shaderProgram(), "lightVector");
    glUniform3fv(uniLightVector, 1, glm::value_ptr(lightVector));

    // update transformation
    Transform& t = entity()->getComponent<Transform>();

    double time = Time::time();
    t.setScale(1.0f + sin((float)time) * 0.2f, 1.0f, 1.0f - sin((float)time) * 0.2f);
    //t.rotate(glm::radians((float)deltaTime * turnSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
    //t.setPosition(0.0f, sin(time) * 0.4f, 0.0f);

    GLint uniTrans = glGetUniformLocation(shaderProgram(), "model");

    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(t.local()));

    Renderer::render();

    // enable wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // disable wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CubeRenderer::createVertexBuffer()
{
    Colour col = getMaterial().getColour();
    //col.print();
    glm::vec3 c = col.vec3();
    //std::cout << "(" << colour.r << ", " << colour.g << ", " << colour.b << ")" << std::endl;

    VertexColour vertices[] = 
    {
    //              x       y      z        colour
        { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), c },    // back
        { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), c }, 
        { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), c }, 
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), c }, 
                                                            
        { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), c },    // front
        { glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), c },
        { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), c },
        { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), c },
                                                                   
        { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), c },    // left
        { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), c },
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), c },
        { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), c },
                                                                   
        { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), c },    // right
        { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), c },
        { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), c },
        { glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), c },
                                                                   
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), c },    // bottom
        { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), c },
        { glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), c },
        { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), c },
                                                                   
        { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), c },    // top
        { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), c },
        { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), c },
        { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), c },
    };

    // vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void CubeRenderer::createElementBuffer()
{
    GLuint elements[] = 
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,
    };

    // element buffer object
    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

