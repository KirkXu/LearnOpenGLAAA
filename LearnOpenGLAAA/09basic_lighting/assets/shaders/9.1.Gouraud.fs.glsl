#version 330
out vec4 FragColor;

in vec3 LightingColor;

uniform vec3 objectColor;

void main()
{
	FragColor = vec4(LightingColor * objectColor, 1.0f);
}