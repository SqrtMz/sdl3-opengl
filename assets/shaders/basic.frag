#version 330 core

in vec4 vertices_coords;
in vec3 vertices_normals;
in vec2 texture_coords;

in vec3 frag_coords;

uniform vec3 light_coords;

uniform vec4 object_color;
uniform vec4 light_color;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixing;

out vec4 frag_color;

void main() {

	float ambient_light_intensity = 0.1;
	vec4 ambient_light = light_color * ambient_light_intensity;

	vec3 norm = normalize(vertices_normals);
	vec3 light_direction = normalize(light_coords - frag_coords);

	float distance_to_light = length(light_coords - frag_coords);

	// float diffusion = max(dot(norm, light_direction), 0.0) / (distance_to_light * distance_to_light);
	float diffusion = max(dot(norm, light_direction), 0.0);
	vec4 diffused_color = diffusion * light_color;

	frag_color = texture(texture0, texture_coords) * object_color * (ambient_light + diffused_color);
}