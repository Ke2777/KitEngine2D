#pragma once
#include "ISystem.h"
#include "Components.h"
#include <GL/glew.h>

class RenderSystem final : public ISystem
{
public:
	virtual void Update(entt::registry& registry, float deltaTime) final override;
};

