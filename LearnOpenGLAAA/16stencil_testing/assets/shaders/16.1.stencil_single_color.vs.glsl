#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    //模型的原点不在中心点时, 放大后的描边和原来模型会有误差,需要沿法线方向平移每个顶点,代码如下:
    //gl_Position = projection * view * model * vec4(aPos + aNormal * scale, 1.0);
}