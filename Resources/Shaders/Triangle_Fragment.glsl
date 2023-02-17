#version 330 core

out vec4 fragcolor;

in vec2 texPosition;

uniform sampler2D tex;

void main()
{
	vec3 texColor = vec3(texture(tex, texPosition));

	fragcolor = vec4(texColor, 1);
}