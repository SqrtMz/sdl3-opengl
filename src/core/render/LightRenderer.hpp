#pragma once

#include "Scene.hpp"
#include "util/Shader.hpp"

class LightRenderer {
	public:
		LightRenderer(Shader& shader);

		void render(Scene& scene);

	private:
		Shader& m_shader;
};