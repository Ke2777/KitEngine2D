#include "Shader.h"


Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{   
    std::string vertexShaderSource = ReadShader(vertexShaderPath);
    std::string fragmentShaderSource = ReadShader(fragmentShaderPath);
    
    GLuint vertexShader = CreateShader(vertexShaderSource, ShaderType::Vertex);
    GLuint fragmentShader = CreateShader(fragmentShaderSource, ShaderType::Fragment);

    CreateProgram(vertexShader, fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}

void Shader::Bind()
{
    glUseProgram(shaderProgram);
}

void Shader::UnBind()
{
    glUseProgram(0);
}

GLint Shader::GetLocation(const std::string& name)
{
    GLint result = glGetUniformLocation(shaderProgram, name.c_str());

    if (result == -1) 
    {
        std::cout << "Location name does not exist: " << name << "!\n";
    }

    return result;
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w)
{
    GLint location = GetLocation(name);
    glUniform4f(location, x, y, z, w);
}

void Shader::SetInt(const std::string& name, int value)
{
    GLint location = GetLocation(name);
    glUniform1i(location, value);
}


void Shader::CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
    shaderProgram = glCreateProgram();

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
}

GLuint Shader::CreateShader(std::string ShaderSource, ShaderType Type)
{
    GLuint shader = 0;
    const char* source = ShaderSource.c_str();

    switch (Type)
    {
    case Shader::ShaderType::Vertex:
        shader = glCreateShader(GL_VERTEX_SHADER);
        break;
    case Shader::ShaderType::Fragment:
        shader = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    }
    
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    
    GLint success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(GL_FALSE == success) 
    {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        GLchar* infoLog = (GLchar*)malloc(length * sizeof(GLchar));

        glGetShaderInfoLog(shader, length, &length, infoLog);
        std::cout << "Failed to compile " << (Type == Shader::ShaderType::Vertex ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << infoLog << std::endl;

        __debugbreak();
    }
    
    return shader;
}

std::string Shader::ReadShader(std::string path)
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

