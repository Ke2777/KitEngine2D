#include "SpriteSystem.h"
#include <SOIL/SOIL.h>

void SpriteSystem::Update(entt::registry& registry, float deltaTime)
{
	auto view = registry.view<SpriteComponent>();

    for (auto [entity, sprite] : view.each()) {
        //if (!fs::exists(sprite.texturePath) || !sprite.init) {
        //    continue;
        //}
        
        constexpr float vertices[] =
        {
             0.5f, 0.5f, 1.0f, 1.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             -0.5f, -0.5f, 0.0f, 0.0f,
             -0.5f, 0.5f, 0.0f, 1.0f,
        };

        constexpr unsigned int indices[] =
        {
            0, 1, 3, // First triangle
            1, 2, 3  // Second triangle
        };

        glGenBuffers(1, &sprite.vbo);
        glGenBuffers(1, &sprite.ebo);

        glBindBuffer(GL_ARRAY_BUFFER, sprite.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite.ebo); //Index array
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        sprite.textureId = SOIL_load_OGL_texture(sprite.texturePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

        glBindTexture(GL_TEXTURE_2D, sprite.textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        sprite.init = true;
    }
}
