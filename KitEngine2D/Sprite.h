#pragma once
#include<string>
#include <GL/glew.h>
#include <memory>

#include "Texture2D.h"
#include "Shader.h"


class Sprite
{
private:
	GLuint VBO;
	GLuint EBO;
	Texture2D texture;
	std::shared_ptr<Shader> shader;

public:
	Sprite(const std::string& spritePath);
	~Sprite();

	void SetShader(const std::shared_ptr<Shader>& shader);
	void Render();

};

