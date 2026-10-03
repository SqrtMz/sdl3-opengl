#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
	public:
		Shader(const std::string& vs_path, const std::string& fs_path);

		void bind();
		void unbind();
		void cleanup();

		unsigned int get_shader_id() const { return m_id; }

		void set_bool(const std::string& name, bool value) const;

		void set_int(const std::string& name, int value) const;

		void set_float(const std::string& name, float value) const;
		void set_float(const std::string& name, std::array<float, 2>& values) const;
		void set_float(const std::string& name, std::array<float, 3>& values) const;
		void set_float(const std::string& name, std::array<float, 4>& values) const;

		void set_mat4(const std::string& name, const glm::mat4& mat4) const;

	private:
		unsigned int m_id;
};