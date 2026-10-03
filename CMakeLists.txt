cmake_minimum_required(VERSION 3.16)

project(
	sdl3-opengl
	VERSION 1.0.0
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(assimp CONFIG REQUIRED)

add_executable(${PROJECT_NAME})

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glad::glad SDL3::SDL3 glm::glm assimp::assimp)
target_link_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})