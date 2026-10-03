#include "Model.hpp"

Model::Model(const std::string& id, std::vector<Mesh>&& meshes) : m_id(id), m_meshes(meshes) {}

void Model::cleanup() {
	for (auto& m : m_meshes) m.cleanup();
	m_meshes.clear();
}