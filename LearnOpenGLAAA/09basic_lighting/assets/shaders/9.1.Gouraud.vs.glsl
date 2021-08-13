#version 330
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;

out vec3 LightingColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float shininess;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);

	// gouraud shading
	vec3 Position = vec3(model * vec4(aPos, 1.0f));
	vec3 Normal = aNormal;

	// ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - Position);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	// specular
	float specularStrength = 1.0f;
	vec3 viewDir = normalize(viewPos - Position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
	vec3 specular = specularStrength * spec * lightColor;

	LightingColor = ambient + diffuse + specular;
}