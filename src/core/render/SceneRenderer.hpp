#pragma once

#include "Scene.hpp"
#include "util/Shader.hpp"

class SceneRenderer {
	public:
		SceneRenderer(Shader& shader);

		void render(Scene& scene);

	private:
		Shader& m_shader;
};