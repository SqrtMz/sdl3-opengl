#pragma once

#include <vector>

#include "Mesh.hpp"

class Model {
	public:
		Model(const std::string& id, std::vector<Mesh>&& meshes);

		const std::string& getId() const { return m_id; }
		std::vector<Mesh>& getMeshes() { return m_meshes; }

		void cleanup();

	private:
		std::string m_id;
		std::vector<Mesh> m_meshes;
};