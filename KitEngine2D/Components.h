#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GL/glew.h>

struct TransformComponent {
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;

    TransformComponent(glm::vec2 position = glm::vec2(0.0f), glm::vec2 scale = glm::vec2(1.0f), float rotation = 0.0f)
        : position(position), scale(scale), rotation(rotation) {}

    glm::mat4 getMatrix() const {
        glm::mat4 matrix(1.0f);
        matrix = glm::translate(matrix, glm::vec3(position, 0.0f));
        matrix = glm::rotate(matrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        matrix = glm::scale(matrix, glm::vec3(scale, 1.0f));
        return matrix;
    }
};

struct CameraComponent {
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    CameraComponent(glm::mat4 viewMatrix = glm::mat4(1.0f), glm::mat4 projectionMatrix = glm::mat4(1.0f))
        : viewMatrix(viewMatrix), projectionMatrix(projectionMatrix) {}
};

struct SpriteComponent {
    std::string texturePath;
    GLuint vbo;
    GLuint ebo;
    GLuint textureId;
    bool init;

    SpriteComponent(std::string texturePath = "")
        : texturePath(texturePath), vbo(0), ebo(0), textureId(0), init(false) {}

    ~SpriteComponent() {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteTextures(1, &textureId);
    }

    void Bind(int slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, textureId);
    }

    void UnBind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

};

struct ShaderComponent {
    GLuint program;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;

    ShaderComponent(std::string vertexShaderPath, std::string fragmentShaderPath)
        : program(0), vertexShaderPath(vertexShaderPath), fragmentShaderPath(fragmentShaderPath){}

   ~ShaderComponent(){
       glDeleteProgram(program);
   }

   void Bind()
   {
       glUseProgram(program);
   }

   void UnBind()
   {
       glUseProgram(0);
   }

   GLint GetLocation(const std::string& name)
   {
       GLint result = glGetUniformLocation(program, name.c_str());

       if (result == -1)
       {
           std::cout << "Location name does not exist: " << name << "!\n";
       }

       return result;
   }

   void SetVec4(const std::string& name, float x, float y, float z, float w)
   {
       GLint location = GetLocation(name);
       glUniform4f(location, x, y, z, w);
   }

   void SetInt(const std::string& name, int value)
   {
       GLint location = GetLocation(name);
       glUniform1i(location, value);
   }

};