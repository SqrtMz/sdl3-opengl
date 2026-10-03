#include "Entity.hpp"

Entity::Entity(const std::string& id, const std::string& model_id) : m_id(id), m_model_id(model_id) {}

Entity::Entity(const std::string& id, const Model& model) : m_id(id), m_model_id(model.getId()) {}

void Entity::setPosition(float x, float y, float z) { m_position = glm::vec3(x, y, z); }

void Entity::setRotation(float x, float y, float z, float angle) { m_rotation = glm::angleAxis(angle, glm::normalize(glm::vec3(x, y, z))); }

void Entity::setScale(float scale) { m_scale = scale; }

void Entity::updateModelMatrix() { m_model_matrix = glm::translate(glm::mat4(1.0), m_position) * glm::mat4_cast(m_rotation) * glm::scale(glm::mat4(1.0), glm::vec3(m_scale)); }