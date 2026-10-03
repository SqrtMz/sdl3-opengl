#include "ModelManager.hpp"

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

ModelManager::ModelManager() {}

void ModelManager::loadModel(const std::string& path) {

	std::vector<Mesh> meshes;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals | aiProcess_CalcTangentSpace | aiProcess_LimitBoneWeights);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP: " << importer.GetErrorString() << std::endl;
		return;
	}

	processNodes(scene->mRootNode, scene, meshes, path.substr(0, path.find_last_of("/\\") + 1));

	auto [it, inserted] = m_models.try_emplace(path, path, std::move(meshes));
	if (!inserted) std::cout << "Could not add the model: " << path << std::endl;
}

void ModelManager::processNodes(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, const std::string& model_directory) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		for (int j = 0; j < mesh->mNumVertices; j++) {
			Vertex vertex;
			vertex.coords.x = mesh->mVertices[j].x;
			vertex.coords.y = mesh->mVertices[j].y;
			vertex.coords.z = mesh->mVertices[j].z;

			vertex.normals.x = mesh->mNormals[j].x;
			vertex.normals.y = mesh->mNormals[j].y;
			vertex.normals.z = mesh->mNormals[j].z;
			
			if (mesh->mTextureCoords[0]) {
				vertex.tex_coords.x = mesh->mTextureCoords[0][j].x;
				vertex.tex_coords.y = mesh->mTextureCoords[0][j].y;
			}
			else vertex.tex_coords = glm::vec2(0.0);

			vertices.push_back(vertex);
		}

		for (int j = 0; j < mesh->mNumFaces; j++) {
			aiFace face = mesh->mFaces[j];
			for (int k = 0; k < face.mNumIndices; k++) indices.push_back(face.mIndices[k]);
		}

		aiString texture_filename;
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		
		Material mesh_material;
		for (auto& t : { aiTextureType_DIFFUSE, aiTextureType_SPECULAR }) {
			for (int j = 0; j < material->GetTextureCount(t); j++) {

				material->GetTexture(t, i, &texture_filename);
				std::string texture_path = model_directory + texture_filename.C_Str();

				m_texture_manager.addTexture(texture_path);

				if (t == aiTextureType_DIFFUSE) mesh_material.diffuse.push_back(texture_path);
				else if (t == aiTextureType_SPECULAR) mesh_material.specular.push_back(texture_path);
			}
		}

		float shininess = 20.0;
		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_SHININESS, shininess));

		mesh_material.shininess = shininess;

		meshes.push_back(Mesh(vertices, indices, mesh_material));
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		processNodes(node->mChildren[i], scene, meshes, model_directory);
	}
}

void ModelManager::cleanup() {
	for (auto& [k, v] : m_models) v.cleanup();
	m_models.clear();
	m_texture_manager.cleanup();
}