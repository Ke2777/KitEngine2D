#include "Sprite.h"

Sprite::Sprite(const std::string& spritePath) : texture(spritePath)
{
    float vertices[] =
    {
         0.5f, 0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         -0.5f, -0.5f, 0.0f, 0.0f,
         -0.5f, 0.5f, 0.0f, 1.0f,
    };

    unsigned int indices[] = 
    {
        0, 1, 3, // First triangle
        1, 2, 3  // Second triangle
    };

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Index array
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

Sprite::~Sprite()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


void Sprite::SetShader(const std::shared_ptr<Shader>& shader)
{
    this -> shader = shader;
}

void Sprite::Render()
{
    if (!shader) 
    {

        return;
    }
    
    texture.Bind();

    shader -> Bind();
    shader -> SetInt("tex", 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
