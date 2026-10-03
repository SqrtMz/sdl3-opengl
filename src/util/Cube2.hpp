#pragma once

#include <vector>
#include <glad/glad.h>

#include "util/Shader.hpp"
#include "util/Texture.hpp"

class Cube2 {
	public:
		Cube2(Shader& shader);

		void draw(int w, int h);

	private:
		Shader& m_shader;
		std::vector<Texture> m_textures;
		unsigned int m_VAO;
};