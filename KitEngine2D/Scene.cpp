#include "Scene.h" 
#include "Entity.h" 

Scene::Scene()
{
    AddSystem<ShaderSystem>();
    AddSystem<SpriteSystem>();
    AddSystem<RenderSystem>();
}

Entity& Scene::CreateEntity()
{
    auto entity = _registry.create();
    _registry.emplace<TransformComponent>(entity);
    _entities.emplace_back(entity, this);
    return _entities.back();
}

void Scene::Update(float deltaTime)
{
    for (auto& system : _systems) 
    {
        system -> Update(_registry, deltaTime);
    }
}
