target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

add_subdirectory(core)
add_subdirectory(util)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})