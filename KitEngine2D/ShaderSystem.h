#pragma once
#include "ISystem.h"
#include "Types.h"

#include <filesystem>
#include <GL/glew.h>
#include "Components.h"
#include <fstream>
#include <sstream>
#include <iostream>


namespace fs = std::filesystem;

class ShaderSystem final : public ISystem
{
public:
	virtual void Update(entt::registry& registry, float deltaTime) final override;

private:
	std::string ReadShader(std::string path);
	GLuint CreateShader(std::string ShaderSource, ShaderType Type);
	GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader);
};

