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
    //ģ�͵�ԭ�㲻�����ĵ�ʱ, �Ŵ�����ߺ�ԭ��ģ�ͻ������,��Ҫ�ط��߷���ƽ��ÿ������,��������:
    //gl_Position = projection * view * model * vec4(aPos + aNormal * scale, 1.0);
}