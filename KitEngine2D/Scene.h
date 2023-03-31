#pragma once
#include <entt/entt.hpp>
#include <vector>
#include <memory>

#include "Components.h"
#include "ISystem.h"
#include "ShaderSystem.h"
#include "RenderSystem.h"
#include "SpriteSystem.h"

class Entity;

class Scene
{
private:
    entt::registry _registry;
    std::vector<Entity> _entities;
    std::vector<std::unique_ptr<ISystem>> _systems;

    friend class Entity;
public:
    Scene();
    Entity& CreateEntity();

    template <typename System, typename... Args>
    void AddSystem(Args&&... args)
    {
        _systems.emplace_back(std::make_unique<System>(std::forward(args)...));
    }

    void Update(float deltaTime);
};