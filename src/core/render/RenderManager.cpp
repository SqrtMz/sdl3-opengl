#include "RenderManager.hpp"

#include <iostream>

#include <glad/glad.h>

RenderManager::RenderManager(int window_width, int window_height) {

	m_shader_manager.add_shader("basic", "assets/shaders/basic.vert", "assets/shaders/basic.frag");
	m_shader_manager.add_shader("scene", "assets/shaders/scene.vert", "assets/shaders/scene.frag");
	m_shader_manager.add_shader("lighting", "assets/shaders/light.vert", "assets/shaders/light.frag");

	m_scene_renderer.emplace(m_shader_manager.get_shader("basic"));

	glViewport(0, 0, window_width, window_height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClearColor(0.1, 0.1, 0.1, 1.0);
}

void RenderManager::render(WindowManager& window_manager, Scene& scene) {

	int w =  window_manager.getWidth();
	int h = window_manager.getHeight();

	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.updateProjectionMatrix(w, h);

	m_scene_renderer->render(scene);
}

void RenderManager::cleanup() {
	m_shader_manager.cleanup();
}