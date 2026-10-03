#pragma once

#include <array>
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

class InputHandler {
	public:
		InputHandler();

		void processEvents(SDL_Event& ev);

		bool isKeyPressed(SDL_Scancode key) { return m_this_frame_pressed_keys[key]; }
		bool isKeyHeld(SDL_Scancode key) { return m_held_keys[key]; }
		bool isKeyReleased(SDL_Scancode key) { return m_this_frame_released_keys[key]; }

		glm::vec2 getMousePosition() { return m_current_position; }
		glm::vec2 getMouseDelta() { return m_mouse_delta_position; }
		bool isMouseButtonPressed(int mouse_button) { return m_this_frame_pressed_mouse_buttons[mouse_button]; }
		bool isMouseButtonHeld(int mouse_button) { return m_held_mouse_buttons[mouse_button]; }
		bool isMouseButtonReleased(int mouse_button) { return m_this_frame_released_mouse_buttons[mouse_button]; }

		void endFrame();
	
	private:
		glm::vec2 m_current_position = glm::vec2(0.0);
		glm::vec2 m_mouse_delta_position = glm::vec2(0.0);
		glm::vec2 m_scroll_delta_position = glm::vec2(0.0);

		std::array<bool, SDL_SCANCODE_COUNT> m_held_keys{};
		std::array<bool, SDL_SCANCODE_COUNT> m_this_frame_pressed_keys{};
		std::array<bool, SDL_SCANCODE_COUNT> m_this_frame_released_keys{};

		std::array<bool, 5> m_held_mouse_buttons{};										//
		std::array<bool, 5> m_this_frame_pressed_mouse_buttons{};						// 1: Left click, 2: Right click, 3: Middle click, 4: Extra 1, 5: Extra 2
		std::array<bool, 5> m_this_frame_released_mouse_buttons{};						//
};