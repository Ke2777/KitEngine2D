#pragma once
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	
	enum class ShaderType 
	{
		Vertex,
		Fragment,
		None
	};

	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
	
	~Shader();

	void Bind();
	void UnBind();

	GLint GetLocation(const std::string& name);
	void SetVec4(const std::string& name, float x, float y, float z, float w);
	void SetInt(const std::string& name, int value);

private:
	GLuint shaderProgram = 0;
	
	void CreateProgram(GLuint vertexShader, GLuint fragmentShader);
	GLuint CreateShader(std::string ShaderSource, ShaderType Type);
	std::string ReadShader(std::string path);
};

