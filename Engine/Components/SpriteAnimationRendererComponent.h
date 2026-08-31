#pragma once
#include "SpriteRendererComponent.h"
#include "Resources/Resource.h"
namespace nu
{
	class SpriteAnimationRendererComponent : public SpriteRendererComponent
	{
	public:
		CLASS_PROTOTYPE(SpriteAnimationRendererComponent)

		void Start() override;
		void Read(const json::value_t& value) override;
		void Update(float dt) override;
	private:
		float m_framesPerSecond = 1.0f;
		float m_frameTimer = 0.0f;
		bool m_loop = true;
		std::string m_textureFramesName;

		unsigned int m_frame;
		res_t<class TextureFrames> m_textureFrames;

	};
}