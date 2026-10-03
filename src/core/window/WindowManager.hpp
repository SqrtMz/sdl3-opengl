#pragma once

#include <string>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "InputHandler.hpp"

class WindowManager {
	public:
		WindowManager(std::string window_title, int width, int height, int vsync);

		void init();
		void swapBuffers();
		void setClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
		void setWindowTitle(std::string window_title) { SDL_SetWindowTitle(m_window, window_title.c_str()); }
		void setVsync(bool vsync) { SDL_GL_SetSwapInterval(vsync); }
		void pollEvents(bool& is_running);
		void cleanup();

		SDL_Window* getWindow() const { return m_window; }
		const int getWidth() const { return m_width; }
		const int getHeight() const { return m_height; }
		const std::string getWindowTitle() const { return m_window_title; }
		InputHandler& getInputHandler() { return m_input_handler; }
		int getVsyncStatus() { return m_vsync; }

	private:
		int m_width;
		int m_height;
		const std::string m_window_title;
		SDL_Window* m_window;
		SDL_GLContext m_context;
		InputHandler m_input_handler;
		int m_vsync;
};