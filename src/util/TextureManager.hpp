#pragma once

#include <string>
#include <unordered_map>

#include "Texture.hpp"

class TextureManager {
	public:
		TextureManager();

		void addTexture(const std::string& path);
		void removeTexture(const std::string& id);
		
		std::unordered_map<std::string, Texture>& getTextures() { return m_textures; }
		Texture& getTexture(const std::string& id) { return m_textures.at(id); }

		void cleanup();

	private:
		std::unordered_map<std::string, Texture> m_textures;
};