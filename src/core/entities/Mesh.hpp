#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>

#include "util/DataStructures.hpp"
#include "util/Shader.hpp"
#include "util/Texture.hpp"

class Mesh {
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Material& material);

		unsigned int getVAO() const { return m_VAO; }
		unsigned int getVerticesNumber() const { return m_vertices_number; }
		void cleanup();

		Material& getMaterial() { return m_material; }

	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;

		unsigned int m_vertices_number;

		Material m_material;
};