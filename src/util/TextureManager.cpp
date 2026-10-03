#include "TextureManager.hpp"

#include <iostream>
#include <filesystem>

TextureManager::TextureManager() {
	addTexture("assets/textures/test.png");
}

void TextureManager::addTexture(const std::string& path) {

	if (!m_textures.contains(path)) {
		auto [it, inserted] = m_textures.try_emplace(path, path);
		if (!inserted) std::cout << "Could not create the texture: " << path << std::endl;
	}
}

void TextureManager::removeTexture(const std::string& id) {
	m_textures.at(id).cleanup();
	m_textures.erase(id);
}

void TextureManager::cleanup() {
	for (auto& [k, v] : m_textures) v.cleanup();
	m_textures.clear();
}