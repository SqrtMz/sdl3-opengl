#include "Camera.hpp"

#include <iostream>

#include "window/InputHandler.hpp"

Camera::Camera() {}

void Camera::setPosition(float x, float y, float z) { m_position = glm::vec3(x, y, z); }

void Camera::moveRight(float inc) {
	glm::vec3 vector = glm::vec3(glm::inverse(m_view_matrix)[0]);
	m_position += glm::vec3(vector.x * inc, 0, vector.z * inc);
}

void Camera::moveLeft(float inc) {
	glm::vec3 vector = -glm::vec3(glm::inverse(m_view_matrix)[0]);
	m_position += glm::vec3(vector.x * inc, 0, vector.z * inc);
}

void Camera::moveUp(float inc) { m_position += glm::vec3(0, inc, 0); }
void Camera::moveDown(float inc) { m_position += glm::vec3(0, -inc, 0); }

void Camera::moveForward(float inc) { m_position += glm::vec3(m_direction.x * inc, 0, -m_direction.z * inc); }
void Camera::moveBackward(float inc) { m_position += glm::vec3(-m_direction.x * inc, 0, m_direction.z * inc); }

void Camera::setRotation(float x, float y) {
	m_direction = glm::vec3(glm::sin(glm::radians(y)), 0.0, glm::cos(glm::radians(y)));
	m_rotation = glm::vec2(x, y);
}

void Camera::rotate(float x, float y) {

	m_rotation += glm::vec2(x, y);

	if (m_rotation.x >= 90) m_rotation.x = 90;
	else if (m_rotation.x <= -90) m_rotation.x = -90;

	if (m_rotation.y > 180) m_rotation.y = -180;
	else if (m_rotation.y < -180) m_rotation.y = 180;

	m_direction = glm::vec3(glm::sin(glm::radians(m_rotation.y)), 0.0, glm::cos(glm::radians(m_rotation.y)));
}

void Camera::updateViewMatrix() {
	m_view_matrix = glm::rotate(glm::mat4(1.0), glm::radians(m_rotation.x), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(1.0), glm::radians(m_rotation.y), glm::vec3(0.0, 1.0, 0.0)) * glm::translate(glm::mat4(1.0), -m_position);
}

void Camera::processInputs(WindowManager& window_manager, float delta_time) {

	InputHandler& input_handler = window_manager.getInputHandler();
	SDL_Window* window = window_manager.getWindow();

	bool is_enabled = SDL_GetWindowRelativeMouseMode(window);

	if (input_handler.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
		SDL_SetWindowRelativeMouseMode(window, !is_enabled);
		if (is_enabled) SDL_WarpMouseInWindow(window, (float)(window_manager.getWidth() / 2), (float)(window_manager.getHeight() / 2));
	}

	if (is_enabled) {
		glm::vec2 rotation = input_handler.getMouseDelta() * m_mouse_sensitivity;
		rotate(rotation.y, rotation.x);
	}

	float move = m_camera_speed * delta_time;

	if (input_handler.isKeyHeld(SDL_SCANCODE_A))		moveLeft(move);
	else if (input_handler.isKeyHeld(SDL_SCANCODE_D))	moveRight(move);

	if (input_handler.isKeyHeld(SDL_SCANCODE_SPACE))	moveUp(move);
	else if (input_handler.isKeyHeld(SDL_SCANCODE_F))	moveDown(move);

	if (input_handler.isKeyHeld(SDL_SCANCODE_W))		moveForward(move);
	else if (input_handler.isKeyHeld(SDL_SCANCODE_S))	moveBackward(move);

	if (input_handler.isKeyHeld(SDL_SCANCODE_0)) setRotation(0, 0);

	updateViewMatrix();
}