#pragma once

#include "window/WindowManager.hpp"
#include "render/RenderManager.hpp"
#include "util/Timer.hpp"
#include "util/ShaderManager.hpp"
#include "Scene.hpp"

class EngineManager {
	public:
		EngineManager(std::string window_title, int width, int height, int target_fps);

		void init();
		void run();
		void processInputs(float tick_time);
		void tick(float tick_time);
		void render(float delta_time);
		void stop();
		void cleanup();

		int getFps() { return m_fps; }
		void setFps(int fps) { m_fps = fps; }

	private:
		WindowManager m_window_manager;
		RenderManager m_render_manager;
		ModelManager m_model_manager;
		TextureManager m_texture_manager;
		Timer m_timer;

		Scene m_scene;

		bool m_running = true;
		int m_fps;

		int m_target_tps = 10;
		int m_target_fps;

		long m_SECOND_NS = 1000000000;
};