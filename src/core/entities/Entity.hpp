#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.hpp"

class Entity {
	public:
		Entity(const std::string& id, const std::string& model_id);
		Entity(const std::string& id, const Model& model);

		const std::string getId() const { return m_id; }
		const std::string getModelId() const { return m_model_id; }

		glm::mat4& getModelMatrix() { return m_model_matrix; }
		glm::vec3& getPosition() { return m_position; }
		glm::quat& getRotation() { return m_rotation; }
		float& getScale() { return m_scale; }

		void updateModelMatrix();

		void setPosition(float x, float y, float z);
		void setRotation(float x, float y, float z, float angle);
		void setScale(float scale);

	private:
		const std::string m_id;
		std::string m_model_id;

		glm::mat4 m_model_matrix = glm::mat4(1.0);
		glm::vec3 m_position = glm::vec3(0.0);
		glm::quat m_rotation = glm::quat(1.0, 0.0, 0.0, 0.0);
		float m_scale = 1.0;
};