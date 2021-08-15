#version 330 core
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;
	float shininess;
};


struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};



out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float shininess;

uniform Material material;
uniform Light light;

void main()
{
	// ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// diffuse
	vec3 norm     = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff    = max(dot(norm, lightDir), 0.0);
	vec3 diffuse  = diff * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;

	// specular
	vec3 viewDir    = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular   = spec * vec3(texture(material.specular, TexCoords)) * light.specular;

	// emissive
	vec3 emissive = vec3(texture(material.emissive, TexCoords));

	vec3 result = ambient + diffuse + specular + emissive;
	FragColor = vec4(result, 1.0);
}