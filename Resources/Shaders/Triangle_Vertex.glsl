#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texturePosition;

out vec2 texPosition;

void main()
{
    texPosition = texturePosition;
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
}