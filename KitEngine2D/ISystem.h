#pragma once
#include <entt/entt.hpp>

struct ISystem 
{

	virtual void Update(entt::registry& registry, float deltaTime) = 0;
	virtual ~ISystem() {};

};