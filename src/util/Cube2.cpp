#include "Cube2.hpp"
#include <iostream>
#include <vector>

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube2::Cube2(Shader& shader) : m_shader(shader) {

	struct Cube2Vertex {
		glm::vec3 pos;
		glm::vec3 col;
		glm::vec2 tex_coords;
	};

	std::vector<Cube2Vertex> vertices = {
		{ {  0.5,  0.5,  0.5 }, { 1.0, 1.0, 1.0 }, { 1.0, 1.0 } }, // +X +Y +Z TOP RIGHT FRONT		(0)
		{ {  0.5, -0.5,  0.5 }, { 1.0, 1.0, 1.0 }, { 1.0, 0.0 } }, // +X -Y +Z BOTTOM RIGHT FRONT	(1)
		{ { -0.5,  0.5,  0.5 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0 } }, // -X +Y +Z TOP LEFT FRONT		(2)
		{ { -0.5, -0.5,  0.5 }, { 1.0, 1.0, 1.0 }, { 0.0, 0.0 } }, // -X -Y +Z BOTTOM LEFT FRONT	(3)
		{ {  0.5,  0.5, -0.5 }, { 1.0, 1.0, 1.0 }, { 1.0, 1.0 } }, // +X +Y -Z TOP RIGHT BACK		(4)
		{ {  0.5, -0.5, -0.5 }, { 1.0, 1.0, 1.0 }, { 1.0, 0.0 } }, // +X -Y -Z BOTTOM RIGHT BACK	(5)
		{ { -0.5,  0.5, -0.5 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0 } }, // -X +Y -Z TOP LEFT BACK		(6)
		{ { -0.5, -0.5, -0.5 }, { 1.0, 1.0, 1.0 }, { 0.0, 0.0 } }, // -X -Y -Z BOTTOM LEFT BACK		(7)
	};

	std::vector<unsigned int> indices = {
		0, 2, 1, 	1, 2, 3, // FRONT FACE
		3, 2, 7, 	7, 2, 6, // LEFT FACE
		5, 7, 6, 	6, 4, 5, // BACK FACE
		5, 4, 1, 	1, 4, 0, // RIGHT FACE
		0, 4, 2, 	2, 4, 6, // TOP FACE
		1, 7, 5, 	3, 7, 1, // BOTTOM FACE
	};

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	unsigned int VBO;																								// Variable to store the reference ID of the new Vertex Buffer Objects
	glGenBuffers(1, &VBO);																							// Writes the reference ID onto the VBO variable

	glBindBuffer(GL_ARRAY_BUFFER, VBO);																				// Links the VBO variable to the actual GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Cube2Vertex), vertices.data(), GL_STATIC_DRAW);			// Calls the VBO buffer, sends the vertices data and tells to draw (see arguments)

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Cube2Vertex), (void*)offsetof(Cube2Vertex, pos));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Cube2Vertex), (void*)offsetof(Cube2Vertex, col));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Cube2Vertex), (void*)offsetof(Cube2Vertex, tex_coords));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Cube2::draw(int w, int h) {

		double time = SDL_GetTicks() / 1000.0;

		glm::mat4 model = glm::mat4(1.0);
		glm::mat4 view = glm::mat4(1.0);
		glm::mat4 proj = glm::mat4(1.0);

		model = glm::scale(model, glm::vec3(0.15, 0.15, 0.15));

		// model = glm::rotate(model, (float)(time * glm::radians(90.0)), glm::vec3(1.0, 1.0, 0.0));		// Diagonal rotation
		// model = glm::rotate(model, (float)glm::radians(45.0), glm::vec3(-1.0, 1.0, 0.0));				// Diagonal static
		// model = glm::rotate(model, (float)(glm::radians(30.0)), glm::vec3(1.0, 0.0, 0.0));				// Front rotated
		model = glm::rotate(model, (float)(time * glm::radians(45.0)), glm::vec3(0.0, 1.0, 0.0));		// Y Rotation

		model = glm::translate(model, glm::vec3(0.0, 0.85 * (-1 + ((std::sin(time * 2.5) / 10) + 0.1)), 0.0));

		proj = glm::perspective(glm::radians(45.0), (double)w / (double)h, 0.1, 100.0);
		proj = glm::translate(proj, glm::vec3(-0.9, -0.9, -3.0));

		m_shader.bind();

		m_shader.set_mat4("model", model);
		m_shader.set_mat4("view", view);
		m_shader.set_mat4("proj", proj); 
		
		if (m_textures.size() > 0) {
			for (int i = 0; i < m_textures.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textures[i].getId());
				m_shader.set_int("texture" + std::to_string(i), i);
			}
		}

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		m_shader.unbind();
}