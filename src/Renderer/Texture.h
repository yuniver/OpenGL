#pragma once
#include "Base.h"
#include <cstdint>
#include <string>

namespace Terric
{
	enum class ImageFormat
	{
		None = 0,
		R8,
		RGB8,
		RGBA8,
		RGBA32F
	};
	struct TextureSpecification
	{
		uint32_t Width = 1;
		uint32_t Height = 1;
		ImageFormat Format = ImageFormat::RGBA8;
		bool GenerateMips = true;
	};
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual bool Load(const std::string& path, bool isTransparent = false) = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual uint32_t GetRendererID() const = 0;
	};
}