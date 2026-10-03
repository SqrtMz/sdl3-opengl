#include "InputHandler.hpp"

#include <iostream>

InputHandler::InputHandler() {}

void InputHandler::processEvents(SDL_Event& ev) {
	switch (ev.type) {
		case SDL_EVENT_KEY_DOWN:
			m_held_keys[ev.key.scancode] = true;
			if (!ev.key.repeat) m_this_frame_pressed_keys[ev.key.scancode] = true;
			break;

		case SDL_EVENT_KEY_UP:
			m_held_keys[ev.key.scancode] = false;
			m_this_frame_released_keys[ev.key.scancode] = true;
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			m_held_mouse_buttons[ev.button.button] = true;
			m_this_frame_pressed_mouse_buttons[ev.button.button] = true;
			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:
			m_held_mouse_buttons[ev.button.button] = false;
			m_this_frame_released_mouse_buttons[ev.button.button] = true;
			break;

		case SDL_EVENT_MOUSE_MOTION:
			m_current_position = glm::vec2(ev.motion.x, ev.motion.y);
			m_mouse_delta_position += glm::vec2(ev.motion.xrel, ev.motion.yrel);
			break;

		case SDL_EVENT_MOUSE_WHEEL:
			m_scroll_delta_position += glm::vec2(ev.wheel.x, ev.wheel.y);
			break;
	}	
}

void InputHandler::endFrame() {
	m_this_frame_pressed_keys.fill(false);
	m_this_frame_released_keys.fill(false);
	m_this_frame_pressed_mouse_buttons.fill(false);
	m_this_frame_released_mouse_buttons.fill(false);
	m_mouse_delta_position = glm::vec2(0.0);
	m_scroll_delta_position = glm::vec2(0.0);
}