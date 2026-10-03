#include "Scene.hpp"

Scene::Scene(ModelManager& model_manager, TextureManager& texture_manager, int w, int h) : m_model_manager(model_manager), m_texture_manager(texture_manager) { updateProjectionMatrix(w, h); }

void Scene::addEntity(Entity&& entity) {
	m_entities.emplace(entity.getId(), std::move(entity));
}

void Scene::removeEntity(const std::string& entity_id) { m_entities.erase(entity_id); }

void Scene::updateProjectionMatrix(int w, int h) {
	m_projection_matrix = glm::perspective(m_FOV, (float)w / (float)h, m_Z_NEAR, m_Z_FAR);
}

void Scene::cleanup() {
	m_entities.clear();
}