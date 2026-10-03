#include "SceneRenderer.hpp"

#include <SDL3/SDL.h>

SceneRenderer::SceneRenderer(Shader& shader) : m_shader(shader) {}

void SceneRenderer::render(Scene& scene) {

	m_shader.bind();
	ModelManager& model_manager = scene.getModelManager();
	TextureManager& texture_manager = model_manager.getTextureManager();

	double time = SDL_GetTicks() / 1000.0;

	std::array<float, 4> object_color = { 1.0, 1.0, 1.0, 1.0 };
	std::array<float, 4> light_color = { 1.0, 1.0, 1.0, 1.0 };

	m_shader.set_float("object_color", object_color);
	m_shader.set_float("light_color", light_color);
	m_shader.set_float("mixing", 0.2);

	std::array<float, 3> light_coords = { 0.0, 0.0, 1.6 };
	m_shader.set_float("light_coords", light_coords);

	for (auto& [k, entity] : scene.getEntities()) {

		Model& model = model_manager.getModel(entity.getModelId());

		int nm = 0;
		for (auto& mesh : model.getMeshes()) {

			Material& mesh_material = mesh.getMaterial();

			if (mesh_material.diffuse.size() > 0) {

				int i = 0;
				for (auto& tx : mesh_material.diffuse) {
					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(GL_TEXTURE_2D, texture_manager.getTexture(tx).getId());
					m_shader.set_int("material.diffuse", i);
					i++;
				}

				for (auto& tx : mesh_material.specular) {
					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(GL_TEXTURE_2D, texture_manager.getTexture(tx).getId());
					m_shader.set_int("material.diffuse", i);
					i++;
				}

				m_shader.set_float("material.shininnes", mesh_material.shininess);

			} else {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture_manager.getTexture("assets/textures/test.png").getId());
				m_shader.set_int("material.diffuse", 0);
				m_shader.set_int("material.specular", 0);
				m_shader.set_float("material.shininnes", mesh_material.shininess);
			}

			m_shader.set_mat4("model_matrix", entity.getModelMatrix());
			m_shader.set_mat4("view_matrix", scene.getCamera().getViewMatrix());
			m_shader.set_mat4("projection_matrix", scene.getProjectionMatrix());

			glBindVertexArray(mesh.getVAO());
			glDrawElements(GL_TRIANGLES, mesh.getVerticesNumber(), GL_UNSIGNED_INT, 0);
			nm++;
		}
	}

	m_shader.unbind();
	glActiveTexture(0);
	glBindVertexArray(0);
}