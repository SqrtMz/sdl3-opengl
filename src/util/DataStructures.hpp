#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 coords;
	glm::vec3 normals;
	glm::vec2 tex_coords;
};

struct ColoredVertex {
	glm::vec3 coords;
	glm::vec3 normals;
	glm::vec3 colors;
	glm::vec2 tex_coords;
};

struct Material {
	std::vector<std::string> diffuse;
	std::vector<std::string> specular;
	float shininess;
};