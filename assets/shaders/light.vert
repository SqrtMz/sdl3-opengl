#version 330 core

layout (location = 0) in vec3 enter_coords;
layout (location = 1) in vec4 enter_rgba;
layout (location = 2) in vec2 enter_texture_coords;

uniform vec4 coords_offset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec4 vertices_coords;
out vec4 vertices_color;
out vec2 texture_coords;

void main() {
	gl_Position = proj * view * model * vec4(enter_coords, 1.0);
	vertices_coords = gl_Position;
	vertices_color = enter_rgba;
	texture_coords = enter_texture_coords;
}