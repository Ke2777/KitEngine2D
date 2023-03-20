#include "RenderSystem.h"

void RenderSystem::Update(entt::registry& registry, float deltaTime)
{
    auto view = registry.view<SpriteComponent, ShaderComponent>();

    for (auto [entity, sprite, shader] : view.each()) {
        
        if (sprite.ebo > 0 && sprite.vbo > 0 && shader.program > 0){
            
            sprite.Bind(0);
            shader.Bind();
            shader.SetInt("tex", 0);

            glBindBuffer(GL_ARRAY_BUFFER, sprite.vbo);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        }   
    }
}
