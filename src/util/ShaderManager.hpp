#pragma once

#include <string>
#include <unordered_map>

#include "Shader.hpp"

class ShaderManager {
	public:
		ShaderManager();

		void add_shader(const std::string& shader_name, const std::string& vx_path, const std::string& fs_path);
		void remove_shader(std::string& shader_name);

		std::unordered_map<std::string, Shader>& get_shaders();
		Shader& get_shader(const std::string& shader_name);
		void cleanup();

	private:
		std::unordered_map<std::string, Shader> m_shaders;
};