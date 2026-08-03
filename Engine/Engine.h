#pragma once
#include "Renderer.h"
#include "Random.h"
#include "Vector2.h"
#include "Input.h"
#include "GameTime.h"
#include "MathUtil.h"
#include "Transform.h"
#include "Actor.h"
#include "Scene.h"
#include "File.h"
#include "Audio.h"
#include "Text.h"
#include "Game.h"
#include "ParticleSystem.h"
#include <vector>
#include <iostream>
#include <string>


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
	};

}