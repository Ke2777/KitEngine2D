#pragma once
#include <string>
#include <GL/glew.h>
#include <SOIL/SOIL.h>


class Texture2D
{
public:
	Texture2D(const std::string& texpath);
	void Bind(int slot = 0);
	void UnBind();


private:
	GLuint textureId;
};

