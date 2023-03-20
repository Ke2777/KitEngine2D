#include "ShaderSystem.h"

void ShaderSystem::Update(entt::registry& registry, float deltaTime)
{
    auto view = registry.view<ShaderComponent>();

    for (auto [entity, shader] : view.each()) {
        //if (!fs::exists(shader.vertexShaderPath) || !fs::exists(shader.fragmentShaderPath) || shader.program == 0) {
        //    continue;
        //}

        std::string vertexShaderSource = ReadShader(shader.vertexShaderPath);
        std::string fragmentShaderSource = ReadShader(shader.fragmentShaderPath);

        GLuint vertexShader = CreateShader(vertexShaderSource, ShaderType::Vertex);
        GLuint fragmentShader = CreateShader(fragmentShaderSource, ShaderType::Fragment);

        shader.program = CreateProgram(vertexShader, fragmentShader);
    }
}

GLuint ShaderSystem::CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (GL_FALSE == success)
    {
        GLint length;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
        GLchar* infoLog = (GLchar*)malloc(length * sizeof(GLchar));

        glGetProgramInfoLog(shaderProgram, length, &length, infoLog);
        std::cout << "Failed to link program\n";
        std::cout << infoLog << std::endl;

        __debugbreak();
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint ShaderSystem::CreateShader(std::string ShaderSource, ShaderType Type)
{
    GLuint shader = 0;
    const char* source = ShaderSource.c_str();

    switch (Type)
    {
    case ShaderType::Vertex:
        shader = glCreateShader(GL_VERTEX_SHADER);
        break;
    case ShaderType::Fragment:
        shader = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    }

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (GL_FALSE == success)
    {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        GLchar* infoLog = (GLchar*)malloc(length * sizeof(GLchar));

        glGetShaderInfoLog(shader, length, &length, infoLog);
        std::cout << "Failed to compile " << (Type == ShaderType::Vertex ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << infoLog << std::endl;

        __debugbreak();
    }

    return shader;
}

std::string ShaderSystem::ReadShader(std::string path)
{
    std::string line;
    std::stringstream ss;
    std::ifstream in;
    in.open(path);

    if (in.is_open())
    {
        while (getline(in, line))
        {
            ss << line << "\n";
        }
    }
    in.close();
    return ss.str();
}