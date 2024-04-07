#pragma once
#include <string>

namespace Terric
{
	class OpenGLTexture
	{
	public:
		static uint32_t GenTexture(const uint32_t width, const uint32_t height);
		static uint32_t LoadTexture(const char* path, const std::string& directory);
	private:

	};
}