#include "WindowManager.hpp"

#include <iostream>
#include <glad/glad.h>

WindowManager::WindowManager(std::string window_title, int width, int height, int vsync) : m_window_title(window_title), m_width(width), m_height(height), m_vsync(!vsync) {

	if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
    }

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	m_window = SDL_CreateWindow(m_window_title.c_str(), m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create the window: %s", SDL_GetError());
    }

	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create the OpenGL context: %s", SDL_GetError());
		SDL_DestroyWindow(m_window);
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize GLAD: %s", SDL_GetError());
	}

	SDL_GL_SetSwapInterval(m_vsync);
}

void WindowManager::swapBuffers() { SDL_GL_SwapWindow(m_window); }

void WindowManager::pollEvents(bool& is_running) {

	SDL_Event ev;

	while(SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_EVENT_QUIT:
				is_running = false;
				break;

			case SDL_EVENT_WINDOW_RESIZED:
				m_width = ev.window.data1;
				m_height = ev.window.data2;
				break;
		}

		m_input_handler.processEvents(ev);
	}
}

void WindowManager::cleanup() {
	SDL_GL_DestroyContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}