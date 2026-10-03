#include "EngineManager.hpp"

#include "SDL3/SDL.h"
#include <vector>
#include <utility>

#include "window/InputHandler.hpp"
#include "util/Shader.hpp"
#include "util/Texture.hpp"
#include "util/Cube2.hpp"
#include "core/entities/Mesh.hpp"
#include "core/entities/Model.hpp"
#include "core/entities/Entity.hpp"

EngineManager::EngineManager(std::string window_title, int width, int height, int target_fps) : m_target_fps(target_fps), m_window_manager(window_title, width, height, (bool)target_fps), m_render_manager(width, height), m_scene(Scene(m_model_manager, m_texture_manager, width, height)) { init(); }

void EngineManager::init() {

	m_model_manager.loadModel("assets/models/cube.obj");
	m_model_manager.loadModel("assets/models/sword/Sting-Sword-lowpoly.obj");
	m_model_manager.loadModel("assets/models/rifle-man/SM_Rifle.fbx");

	std::vector<Entity> entities;
	int i = 0;
	for (const auto& [k, mod] : m_model_manager.getModels()) {
		entities.push_back(Entity(mod.getId(), mod));
		i++;
	}

	entities.push_back(Entity("cube1", m_model_manager.getModel("assets/models/cube.obj")));

	for (auto& e : entities) {
		m_scene.addEntity(std::move(e));
	}

	m_scene.getEntity("cube1").setPosition(0.0, -4.0, 0.0);
	m_scene.getEntity("cube1").setScale(5);
	m_scene.getEntity("cube1").updateModelMatrix();

	m_scene.getEntity("assets/models/sword/Sting-Sword-lowpoly.obj").setPosition(-1.0, -1.0, 1.0);
	m_scene.getEntity("assets/models/sword/Sting-Sword-lowpoly.obj").setRotation(0.0, 1.0, 0.0, 180.0);
	m_scene.getEntity("assets/models/sword/Sting-Sword-lowpoly.obj").setScale(0.05);
	m_scene.getEntity("assets/models/sword/Sting-Sword-lowpoly.obj").updateModelMatrix();

	m_scene.getEntity("assets/models/rifle-man/SM_Rifle.fbx").setPosition(2.5, -1.0, 0.5);
	m_scene.getEntity("assets/models/rifle-man/SM_Rifle.fbx").setRotation(1.0, 1.0, 0.0, 180.0);
	m_scene.getEntity("assets/models/rifle-man/SM_Rifle.fbx").setScale(0.05);
	m_scene.getEntity("assets/models/rifle-man/SM_Rifle.fbx").updateModelMatrix();

	m_scene.getCamera().moveBackward(3);
}

void EngineManager::run() {

	Cube2 cube2(m_render_manager.getShaderManager().get_shader("lighting"));

	float tick_time = 1000.0 / m_target_tps;
	float frame_time = (m_target_fps > 0) ? 1000.0 / m_target_fps : 0;						// If 0, then relies in Vsync

	m_timer.setLastTimes();
	float delta_tick = 0;																	// Number of ticks that must be updated
	float delta_frame = 0;																	// Number of frames that must be rendered

	m_running = true;
	while (m_running) {
		m_window_manager.pollEvents(m_running);
		m_timer.setCurrentTime();

		delta_tick += m_timer.getDeltaTimeMS() / tick_time;								// Adds a normalized quantity until reach a value of 1, that indicates that a new tick/frame is required
		delta_frame += m_timer.getDeltaTimeMS() / frame_time;							//

		if (m_target_fps <= 0 || delta_frame >= 1) processInputs(m_timer.getFrameDeltaTimeMS());

		if (delta_tick >= 1) {
			tick(tick_time);
			delta_tick--;

			// m_timer.printTickDeltaTimeMS();
			m_timer.swapTickTime();
		}

		if (m_target_fps <= 0 || delta_frame >= 1) {
			render(m_timer.getFrameDeltaTimeMS());
			cube2.draw(m_window_manager.getWidth(), m_window_manager.getHeight());
			delta_frame--;

			// m_timer.printFrameDeltaTimeMS();
			m_timer.swapFrameTime();
		}

		m_window_manager.getInputHandler().endFrame();
		m_timer.swapTime();
	}

	cleanup();
}

void EngineManager::render(float delta_time) {
	m_window_manager.swapBuffers();
	m_render_manager.render(m_window_manager, m_scene);
}

void EngineManager::tick(float tick_time) {

	Entity& ent = m_scene.getEntity("assets/models/cube.obj");

	float time = SDL_GetTicks() / 1000.0;

	// ent.set_rotation( 1.0, 1.0, 0.0, (float)(time * glm::radians(45.0))); 		// Diagonal rotation
	// ent.set_rotation(-1.0, 1.0, 0.0, (float)(glm::radians(45.0))); 				// Diagonal static
	// ent.set_rotation( 1.0, 0.0, 0.0, (float)(glm::radians(30.0))); 				// Front rotated
	ent.setRotation( 0.0, 1.0, 0.0, (float)(time * glm::radians(45.0))); 		// Y Rotation

	ent.setPosition(0.0, std::sin(time * 2.5) / 10, 0.0);

	ent.updateModelMatrix();
}

void EngineManager::processInputs(float delta_time) {
	m_scene.getCamera().processInputs(m_window_manager, delta_time);
}

void EngineManager::stop() {
	m_running = false;
}

void EngineManager::cleanup() {
	m_window_manager.cleanup();
	m_render_manager.cleanup();
	m_scene.cleanup();
	m_model_manager.cleanup();
}