#include <iostream>
#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "core/EngineManager.hpp"

int main(int argc, char* argv[]) {

	EngineManager engine("Mz's SDL OpenGL Test", 1280, 1280, 210);

	try { engine.run(); }
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}