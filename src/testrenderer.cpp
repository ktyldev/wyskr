#include "testrenderer.hpp"

#include <vector>
#include <iostream>


TestRenderer::TestRenderer()
{
}

TestRenderer::~TestRenderer()
{
}

bool TestRenderer::Initialise()
{
    CreateVertexBuffer();
    CreateElementBuffer();

    CompileShaders();
    SetShaderAttributes();

    return true;
}

GLuint TestRenderer::LoadShaders(const char* vertexPath, const char* fragmentPath)
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

void TestRenderer::CompileShaders()
{
    printf("compiling shaders...\n");
    shaderProgram_ = LoadShaders(
        "src/shaders/shader.vert", 
        "src/shaders/shader.frag");

    glUseProgram(shaderProgram_);
}

void TestRenderer::SetShaderAttributes()
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

void TestRenderer::CreateVertexBuffer()
{
    VertexColour vertices[] = 
    {
    //              x       y               colour
        { glm::vec2(-0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f) }, // top left
        { glm::vec2( 0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f) }, // top right   
        { glm::vec2( 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f) }, // bottom right
        { glm::vec2(-0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // bottom left  
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

void TestRenderer::CreateElementBuffer()
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

