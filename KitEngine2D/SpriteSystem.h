#pragma once
#include "ISystem.h"
#include <filesystem>
#include <GL/glew.h>
#include "Components.h"


namespace fs = std::filesystem;

class SpriteSystem final : public ISystem
{
public:
	virtual void Update(entt::registry& registry, float deltaTime) final override;
};

