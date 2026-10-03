target_sources(${PROJECT_NAME} PRIVATE
	EngineManager.hpp
	EngineManager.cpp
	Scene.hpp
	Scene.cpp
	Camera.hpp
	Camera.cpp
)

add_subdirectory(entities)
add_subdirectory(render)
add_subdirectory(window)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})