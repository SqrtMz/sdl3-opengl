#include "ShaderManager.hpp"

#include <iostream>

ShaderManager::ShaderManager() {}

void ShaderManager::add_shader(const std::string& shader_name, const std::string& vx_path, const std::string& fs_path) {

	auto [it, inserted] = m_shaders.try_emplace(shader_name, Shader(vx_path, fs_path));

	if (!inserted) std::cout << "Could not create the shader: " << shader_name << std::endl;
}

void ShaderManager::remove_shader(std::string& shader_name) {
	m_shaders.at(shader_name).cleanup();
	m_shaders.erase(shader_name);
}

std::unordered_map<std::string, Shader>& ShaderManager::get_shaders() { return m_shaders; }

Shader& ShaderManager::get_shader(const std::string& shader_name) { return m_shaders.at(shader_name); }

void ShaderManager::cleanup() {
	for (auto& [k, v] : m_shaders) { v.cleanup(); }
	m_shaders.clear(); 
}