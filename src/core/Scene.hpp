#pragma once

#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"
#include "entities/Entity.hpp"
#include "util/ShaderManager.hpp"
#include "util/Texture.hpp"
#include "entities/ModelManager.hpp"

class Scene {
	public:
		Scene(ModelManager& model_manager, TextureManager& texture_manager, int w, int h);

		void addEntity(Entity&& entity);
		void removeEntity(const std::string& entity_id);
		std::unordered_map<std::string, Entity>& getEntities() { return m_entities; }
		Entity& getEntity(const std::string& entity_id) { return m_entities.at(entity_id); }

		glm::mat4& getProjectionMatrix() { return m_projection_matrix; }		
		void updateProjectionMatrix(int w, int h);

		Camera& getCamera() { return m_camera; }

		ModelManager& getModelManager() { return m_model_manager; }

		void cleanup();

	private:
		std::unordered_map<std::string, Entity> m_entities;

		glm::mat4 m_projection_matrix = glm::mat4(1.0);
		float m_Z_NEAR = 0.01;
		float m_Z_FAR = 1000.0;
		float m_FOV = glm::radians(90.0);

		Camera m_camera;

		ModelManager& m_model_manager;
		TextureManager& m_texture_manager;
};