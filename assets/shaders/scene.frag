#version 330 core

in vec4 coords;
in vec3 normal;
in vec2 tex_coords;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform vec4 varying_color;
uniform Material material;

out vec4 frag_color;

void main() {
	frag_color = texture(material.diffuse, tex_coords);
}