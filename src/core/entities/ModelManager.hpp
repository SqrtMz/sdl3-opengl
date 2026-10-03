#pragma once

#include <string>
#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Model.hpp"
#include "util/TextureManager.hpp"
#include "util/DataStructures.hpp"

class ModelManager {
	public:
		ModelManager();

		void loadModel(const std::string& path);

		std::unordered_map<std::string, Model>& getModels() { return m_models; }
		Model& getModel(const std::string& id) { return m_models.at(id); }

		TextureManager& getTextureManager() { return m_texture_manager; }

		void cleanup();

	private:
		std::unordered_map<std::string, Model> m_models;
		TextureManager m_texture_manager;

		void processNodes(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, const std::string& model_directory);
};