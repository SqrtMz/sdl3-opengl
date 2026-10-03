#version 330 core

layout (location = 0) in vec3 enter_coords;
layout (location = 1) in vec3 enter_normals;
layout (location = 2) in vec2 enter_texture_coords;

uniform vec4 coords_offset;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec4 vertices_coords;
out vec3 vertices_normals;
out vec2 texture_coords;

out vec3 frag_coords;

void main() {
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(enter_coords, 1.0);

	vertices_coords = gl_Position;
	vertices_normals = mat3(transpose(inverse(model_matrix))) * enter_normals;
	texture_coords = enter_texture_coords;

	frag_coords = vec3(model_matrix * vec4(enter_coords, 1.0));
}