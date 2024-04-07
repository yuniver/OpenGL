#pragma once
#include "../../Renderer/Texture.h"

namespace Terric
{
	class OpenGLTexture :public Texture
	{
	public:
		virtual ~OpenGLTexture();

		void Bind(uint32_t slot = 0) const;

		virtual bool Load(const std::string& path, bool isTransparent) override;

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		virtual uint32_t GetRendererID() const override { return m_RendererID; }
	private:
		uint32_t m_RendererID;
		bool isInited = false;
		std::string m_Path;
		uint32_t m_Width, m_Height, m_BPP;
	};
}