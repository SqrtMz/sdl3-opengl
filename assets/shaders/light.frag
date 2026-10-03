#version 330 core

in vec4 vertices_coords;
in vec4 vertices_rgba;
in vec2 texture_coords;

uniform vec4 varying_color;

out vec4 frag_color;

void main() {
	frag_color = vec4(1.0);
}