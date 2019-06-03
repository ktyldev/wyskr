#include "cuberenderer.hpp"

CubeRenderer::CubeRenderer() : CubeRenderer(
    "src/shaders/shader.vert",
    "src/shaders/shader.frag") 
{
}

CubeRenderer::CubeRenderer(std::string vsPath, std::string fsPath) :
    Renderer(vsPath, fsPath)
{
}

bool CubeRenderer::initialise()
{
    return Renderer::initialise();
}

void CubeRenderer::update()
{
    Renderer::update();

    // TODO: factor out to non-renderer class
    double time = Time::time();

    float turnSpeed = 50.0f;

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians((float)time * turnSpeed), glm::vec3(0.0f, 0.0f, 1.0f)); 
    glm::vec4 result = trans * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    GLint uniTrans = glGetUniformLocation(shaderProgram(), "model");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
}

void CubeRenderer::render()
{
    Renderer::render();

    // enable wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // disable wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CubeRenderer::setColour(Colour& colour)
{
    colour_ = colour.vec3();
}

void CubeRenderer::setShaderAttributes()
{
    int stride = sizeof(VertexColour);
    // get reference to 'position' input of vertex shader
    GLint posAttrib = glGetAttribLocation(shaderProgram(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(
        posAttrib, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        stride, 
        0);

    GLint colAttrib = glGetAttribLocation(shaderProgram(), "colour");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(
        colAttrib,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(3 * sizeof(float))); // offset read position
}

void CubeRenderer::createVertexBuffer()
{
    auto c1 = Colour(0.0f, 0.0f, 1.0f).vec3();
    auto c2 = Colour(0.0f, 1.0f, 0.0f).vec3();
    auto c3 = Colour(0.0f, 1.0f, 1.0f).vec3();
    auto c4 = Colour(1.0f, 0.0f, 0.0f).vec3();
    auto c5 = Colour(1.0f, 0.0f, 1.0f).vec3();
    auto c6 = Colour(1.0f, 1.0f, 0.0f).vec3();

    VertexColour vertices[] = 
    {
    //              x       y      z        colour
        { glm::vec3(-0.5f,  0.5f, -0.5f), c1 }, 
        { glm::vec3( 0.5f,  0.5f, -0.5f), c1 }, 
        { glm::vec3( 0.5f, -0.5f, -0.5f), c1 }, 
        { glm::vec3(-0.5f, -0.5f, -0.5f), c1 }, 

        { glm::vec3(-0.5f, -0.5f,  0.5f), c2 },
        { glm::vec3( 0.5f, -0.5f,  0.5f), c2 },
        { glm::vec3( 0.5f,  0.5f,  0.5f), c2 },
        { glm::vec3(-0.5f,  0.5f,  0.5f), c2 },

        { glm::vec3(-0.5f,  0.5f,  0.5f), c3 },
        { glm::vec3(-0.5f,  0.5f, -0.5f), c3 },
        { glm::vec3(-0.5f, -0.5f, -0.5f), c3 },
        { glm::vec3(-0.5f, -0.5f,  0.5f), c3 },

        { glm::vec3( 0.5f,  0.5f,  0.5f), c4 },
        { glm::vec3( 0.5f,  0.5f, -0.5f), c4 },
        { glm::vec3( 0.5f, -0.5f, -0.5f), c4 },
        { glm::vec3( 0.5f, -0.5f,  0.5f), c4 },

        { glm::vec3(-0.5f, -0.5f, -0.5f), c5 },
        { glm::vec3( 0.5f, -0.5f, -0.5f), c5 },
        { glm::vec3( 0.5f, -0.5f,  0.5f), c5 },
        { glm::vec3(-0.5f, -0.5f,  0.5f), c5 },

        { glm::vec3(-0.5f,  0.5f, -0.5f), c6 },
        { glm::vec3( 0.5f,  0.5f, -0.5f), c6 },
        { glm::vec3( 0.5f,  0.5f,  0.5f), c6 },
        { glm::vec3(-0.5f,  0.5f,  0.5f), c6 },
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

