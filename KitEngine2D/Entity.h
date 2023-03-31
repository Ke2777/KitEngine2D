#pragma once
#include <entt/entt.hpp>
#include "Scene.h"

class Entity
{
private:
	entt::entity _id = entt::null;
	Scene* _scene = nullptr;

public:
	Entity(entt::entity id, Scene* scene) 
	{
		_id = id;
		_scene = scene;
	}

	template <typename Component, typename... Args>
	Component& AddComponent(Args&&... args)
	{
		return	_scene->_registry.emplace<Component>(_id, std::forward<Args>(args)...);
	}

	template <typename Component>
	void RemoveComponent()
	{
		_scene->_registry.remove<Component>(_id);
	}

	template <typename Component>
	Component& GetComponent()
	{
		return _scene->_registry.get<Component>(_id);
	}
};
