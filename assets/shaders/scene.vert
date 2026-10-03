#version 330 core

layout (location = 0) in vec3 enter_coords;
layout (location = 1) in vec3 enter_normal;
layout (location = 2) in vec2 enter_tex_coords;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec4 coords;
out vec3 normal;
out vec2 tex_coords;

void main() {
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(enter_coords, 1.0);

	coords = gl_Position;
	normal = enter_normal;
	tex_coords = enter_tex_coords;
}