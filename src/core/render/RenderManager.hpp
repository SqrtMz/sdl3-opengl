#pragma once

#include <optional>

#include "window/WindowManager.hpp"
#include "Scene.hpp"
#include "SceneRenderer.hpp"
#include "util/ShaderManager.hpp"
#include "util/TextureManager.hpp"
#include "entities/ModelManager.hpp"

class RenderManager {
	public:
		RenderManager(int window_width, int window_height);

		void init();
		void render(WindowManager& window_manager, Scene& scene);
		void cleanup();

		ShaderManager& getShaderManager() { return m_shader_manager; }

	private:
		ShaderManager m_shader_manager;
		TextureManager m_texture_manager;

		std::optional<SceneRenderer> m_scene_renderer;
};