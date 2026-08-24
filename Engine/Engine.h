#pragma once
#include "Renderer/Renderer.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Input/Input.h"
#include "Core/GameTime.h"
#include "Math/MathUtil.h"
#include "Math/Transform.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Core/File.h"
#include "Audio/Audio.h"
#include "Renderer/Text.h"
#include "Framework/Game.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Texture.h"
#include "Resources/ResourceManager.h"
#include "Serialization/Json.h"
#include "Core/StringUtils.h"
#include "Core/Factory.h"
#include "Physics/Physics.h"
#include <SDL3/SDL.h>


namespace nu 
{
	class Engine
	{
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();
		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer(){ return m_renderer; }
		Time& GetTime(){ return m_time; }
		Audio& GetAudio() { return m_audio; }
		ParticleSystem& GetPS() { return m_particleSystem; }
		Physics& GetPhysics() { return m_physics; }


		//Singleton stuff 
		Engine(const Engine&) = delete;
		Engine& operator =(const Engine&) = delete;
	private:
		Engine() = default;
		Input m_input;
		Renderer m_renderer;
		Time m_time;
		Audio m_audio;
		ParticleSystem m_particleSystem;
		Physics m_physics;
	};

}