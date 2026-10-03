#include "Shader.hpp"

Shader::Shader(const std::string& vs_path, const std::string& fs_path) {
	std::string vss_code, fss_code;																// Vertex shader string code & Fragment shader string code
	std::ifstream vs_file, fs_file;

	vs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vs_file.open(vs_path);
		fs_file.open(fs_path);

		std::stringstream vs_stream, fs_stream;

		vs_stream << vs_file.rdbuf();
		fs_stream << fs_file.rdbuf();

		vs_file.close();
		fs_file.close();

		vss_code = vs_stream.str();
		fss_code = fs_stream.str();

	} catch(std::ifstream::failure e) {
		std::cout << '\n' << e.what() << " " << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		return;
	}

	const char* vs_code = vss_code.c_str();
	const char* fs_code = fss_code.c_str();

	unsigned int vertex_shader, fragment_shader;												// Creates the reference ID for the new vertex and fragmet shaders

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);											// stores in the variables the reference IDs
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader, 1, &vs_code, nullptr);										// Attach the vertex shader code to the shader created
	glCompileShader(vertex_shader);																// Compiles the vertex shader

	int success;																				// The build status of a shader can be checked by creating a variable where the result will be given
	char info_log[512];																			// A buffer for the error information (if any)

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);									// This function writes on success a bool wether there was an error or not
	if (!success) {																				// In case of error on shader compilation, this statement will
		glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);								// Retrieve the error information and save it to info_log
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;	// Then can be printed
	}

	glShaderSource(fragment_shader, 1, &fs_code, nullptr);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	m_id = glCreateProgram();																	// Creates a new shader program and stores the reference ID into the variable

	glAttachShader(m_id, vertex_shader);														// Attach shaders and link the shader program
	glAttachShader(m_id, fragment_shader);

	glLinkProgram(m_id);

	glGetProgramiv(m_id, GL_LINK_STATUS, &success);												// Same logic as shader compilation, but with different functions and arguments since this time is a shader program
	if (!success) {
		glGetProgramInfoLog(m_id, 512, nullptr, info_log);
		std::cout << "ERROR::PROGRAM_SHADER::LINKING_FAILED\n" << info_log << std::endl;
	}

	glDeleteShader(vertex_shader);																// Once the linking process has been done successfully, the shader program can be used
	glDeleteShader(fragment_shader);															// And the shader objects used to buit that shader program can be deleted
}

void Shader::bind() { glUseProgram(m_id); }
void Shader::unbind() { glUseProgram(0); }

void Shader::cleanup() {
	unbind();
	if (m_id != 0) glDeleteProgram(m_id);
}

void Shader::set_bool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::set_int(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, std::array<float, 2>& values) const {
	glUniform2f(glGetUniformLocation(m_id, name.c_str()), values[0], values[1]);
}

void Shader::set_float(const std::string& name, std::array<float, 3>& values) const {
	glUniform3f(glGetUniformLocation(m_id, name.c_str()), values[0], values[1], values[2]);
}

void Shader::set_float(const std::string& name, std::array<float, 4>& values) const {
	glUniform4f(glGetUniformLocation(m_id, name.c_str()), values[0], values[1], values[2], values[3]);
}

void Shader::set_mat4(const std::string& name, const glm::mat4& mat4) const {
	glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
}