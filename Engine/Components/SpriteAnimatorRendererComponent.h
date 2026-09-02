#pragma once
#include "SpriteRendererComponent.h"
#include "Resources/ResourceManager.h"
#include <map>

namespace nu
{
	class SpriteAnimatorRendererComponent : public SpriteRendererComponent
	{
	public :
		CLASS_PROTOTYPE(SpriteAnimatorRendererComponent)

		struct SpriteAnimation
		{
			std::string name;
			float framesPerSecond{ 10.0f };
			bool loop{ true };
			res_t<class TextureFrames> textureFrames;
		};

		void Start() override;
		void Update(float dt) override;
		void Play(const std::string& name, bool restart = false);

		void SetPause(float pause = true) { m_pause = pause; }
		bool GetPause() const { return m_pause; }
		void Read(const json::value_t& value) override;

		const std::string& GetCurrentAnimation() const { return m_currentAnimation; }

		unsigned int GetFrame() const { return m_frame; }
		bool IsAnimationDone() const;
		const std::string& GetAnimationName() const { return m_spriteAnimation.name; }

	private:
		unsigned int m_frame = 0;
		float m_frameTimer = 0.0f;
		bool m_pause = false;
		
		std::string m_currentAnimation;

		std::string m_defaultAnimationName;

		SpriteAnimation m_spriteAnimation;
		std::map<std::string, SpriteAnimation> m_spriteAnimations;

	};
}