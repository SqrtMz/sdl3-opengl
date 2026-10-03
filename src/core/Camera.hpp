#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window/WindowManager.hpp"

class Camera {
	public:
		Camera();

		glm::mat4& getViewMatrix() { return m_view_matrix; }
		glm::vec3& getPosition() { return m_position; }
		glm::vec2& getRotation() { return m_rotation; }

		void processInputs(WindowManager& window_manager, float delta_time);

		void updateViewMatrix();

		void setPosition(float x, float y, float z);
		void moveForward(float inc);
		void moveBackward(float inc);
		void moveLeft(float inc);
		void moveRight(float inc);
		void moveUp(float inc);
		void moveDown(float inc);

		void setRotation(float x, float y);
		void rotate(float x, float y);

	private:
		glm::mat4 m_view_matrix = glm::mat4(1.0);
		glm::vec3 m_position = glm::vec3(0.0);
		glm::vec2 m_rotation = glm::vec2(0.0);
		glm::vec3 m_direction = glm::vec3(0.0, 0.0, 1.0);

		float m_mouse_sensitivity = 0.25;
		float m_camera_speed = 0.005;
};