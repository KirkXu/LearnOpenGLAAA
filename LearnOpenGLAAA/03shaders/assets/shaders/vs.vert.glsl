#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 ourColor;  // output a color to fragment shader

uniform float offsetF;

void main()
{
	gl_Position = vec4(aPos.x + offsetF, aPos.y, aPos.z, 1.0);
	ourColor = aColor;
}