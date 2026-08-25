#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"
namespace nu
{
	class SpriteAnimationRendererComponent : public RendererComponent
	{
	public:
		CLASS_PROTOTYPE(SpriteAnimationRendererComponent)

		// Inherited via RendererComponent
		void Draw(const Renderer& renderer) override;
		void Read(const json::value_t& value) override;
		void Update(float dt) override;
	private:
		float m_framesPerSecond = 1.0f;
		float m_frameTimer = 0.0f;
		bool m_loop = true;

		unsigned int m_frame;
		res_t<class TextureFrames> m_textureFrames;

	};
}