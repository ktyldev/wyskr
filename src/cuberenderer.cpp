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

    // TODO: these things are being done by the shader, shouldn't be in update

    // update lighting
    glm::vec3 ambientColour = glm::vec3(0.0f, 0.3f, 0.3f);
    GLint uniAmbient = glGetUniformLocation(shaderProgram(), "ambient");
    glUniform3fv(uniAmbient, 1, glm::value_ptr(ambientColour));

    // directional
    glm::vec3 lightVector = glm::vec3(-0.8f, 0.2f, 0.2f);
    GLint uniLightVector = glGetUniformLocation(shaderProgram(), "lightVector");
    glUniform3fv(uniLightVector, 1, glm::value_ptr(lightVector));

    // update transformation
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians((float)time * turnSpeed), glm::vec3(0.0f, 1.0f, 0.0f)); 
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

    GLint normalAttrib = glGetAttribLocation(shaderProgram(), "normal");
    glEnableVertexAttribArray(normalAttrib);
    glVertexAttribPointer(
        normalAttrib,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(3 * sizeof(float)));

    GLint colAttrib = glGetAttribLocation(shaderProgram(), "colour");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(
        colAttrib,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(6 * sizeof(float))); // offset read position
}

void CubeRenderer::createVertexBuffer()
{
    VertexColour vertices[] = 
    {
    //              x       y      z        colour
        { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), colour_ },    // back
        { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), colour_ }, 
        { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), colour_ }, 
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), colour_ }, 
                                                            
        { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), colour_ },    // front
        { glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), colour_ },
        { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), colour_ },
        { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), colour_ },
                                                                   
        { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), colour_ },    // left
        { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), colour_ },
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), colour_ },
        { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), colour_ },
                                                                   
        { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), colour_ },    // right
        { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), colour_ },
        { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), colour_ },
        { glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), colour_ },
                                                                   
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), colour_ },    // bottom
        { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), colour_ },
        { glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), colour_ },
        { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), colour_ },
                                                                   
        { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), colour_ },    // top
        { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), colour_ },
        { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), colour_ },
        { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), colour_ },
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

