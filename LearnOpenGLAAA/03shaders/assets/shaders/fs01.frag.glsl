#version 330 core
out vec4 FragColor;

in vec3  ourColor;

uniform float colorFactor;

void main()
{
	FragColor = vec4(ourColor * colorFactor, 1.0f);
}