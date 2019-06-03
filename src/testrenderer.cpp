#include "testrenderer.hpp"

#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"

#define FIELD_OF_VIEW   60.0f

TestRenderer::TestRenderer()
{
}

TestRenderer::~TestRenderer()
{
}

bool TestRenderer::initialise()
{
    createVertexBuffer();
    createElementBuffer();

    compileShaders();
    setShaderAttributes();

    return true;
}

void TestRenderer::update()
{
    double time = Time::time();

    float turnSpeed = 50.0f;

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians((float)time * turnSpeed), glm::vec3(0.0f, 0.0f, 1.0f)); 
    glm::vec4 result = trans * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    GLint uniTrans = glGetUniformLocation(shaderProgram_, "model");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
}

void TestRenderer::updateView()
{
    GLint uniView = glGetUniformLocation(shaderProgram_, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(Camera::main()->view()));
}

void TestRenderer::updateProjection()
{
    GLuint uniProjection = glGetUniformLocation(shaderProgram_, "projection");
    glUniformMatrix4fv(uniProjection, 1, GL_FALSE, glm::value_ptr(Camera::main()->projection()));
}

void TestRenderer::render()
{
    // enable wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // update transformations
    updateView();
    updateProjection();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // disable wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void TestRenderer::setColour(Colour& colour)
{
    colour_ = colour.vec3();
}

GLuint TestRenderer::loadShaders(const char* vertexPath, const char* fragmentPath)
{
    printf("reading shaders...\n");
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // read shaders
    std::string vertShaderStr = readFile(vertexPath);
    std::string fragShaderStr = readFile(fragmentPath);
    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // compile vertex shader
    printf("compiling vertex shader...\n");
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // check vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError(logLength > 1 ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
    if (logLength > 1)
    {
        std::cout << &vertShaderError[0] << std::endl;
    }

    // compile fragment shader
    printf("compiling fragment shader...\n");
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    // check fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError(logLength > 1 ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    if (logLength > 1)
    {
        std::cout << &fragShaderError[0] << std::endl;
    }

    printf("linking program...\n");
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError(logLength > 1 ? logLength : 1);
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    if (logLength > 1)
    {
        std::cout << &programError[0] << std::endl;
    }

    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}

void TestRenderer::compileShaders()
{
    printf("compiling shaders...\n");
    shaderProgram_ = loadShaders(
        "src/shaders/shader.vert", 
        "src/shaders/shader.frag");

    glUseProgram(shaderProgram_);
}

void TestRenderer::setShaderAttributes()
{
    int stride = 5 * sizeof(float);
    // get reference to 'position' input of vertex shader
    GLint posAttrib = glGetAttribLocation(shaderProgram_, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(
        posAttrib, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        stride, 
        0);

    GLint colAttrib = glGetAttribLocation(shaderProgram_, "colour");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(
        colAttrib,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(2 * sizeof(float))); // offset red position
}

void TestRenderer::createVertexBuffer()
{
    VertexColour vertices[] = 
    {
    //              x       y               colour
        { glm::vec2(-0.5f,  0.5f), colour_ }, // top left
        { glm::vec2( 0.5f,  0.5f), colour_ }, // top right   
        { glm::vec2( 0.5f, -0.5f), colour_ }, // bottom right
        { glm::vec2(-0.5f, -0.5f), colour_ }, // bottom left  
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

void TestRenderer::createElementBuffer()
{
    GLuint elements[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    // element buffer object
    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

