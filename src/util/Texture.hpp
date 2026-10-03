#pragma once

#include <string>
#include <glad/glad.h>

class Texture {
	public:
		Texture(const std::string& path);

		void cleanup();

		const unsigned int getId() const { return m_id; }

	private:
		int m_width;
		int m_height;
		int m_color_channels;

		unsigned int m_id;
};