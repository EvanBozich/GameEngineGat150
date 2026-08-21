// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "Engine.h"

namespace nu
{

	bool Engine::Initialize()
	{
		m_renderer.Initialize("Game engine", 1280, 1024);
		m_particleSystem.Initialize(10000);
		m_input.Initialize();
		m_audio.Initialize();
		m_physics.Initialize();

		return true;
	}

	void Engine::Update()
	{
		m_time.Tick();
		m_input.Update();
		m_audio.Update();
		m_particleSystem.Update(m_time.GetDeltaTime());
		m_physics.Update(m_time.GetDeltaTime());

	}

	void Engine::Shutdown()
	{
		m_physics.Shutdown();
		m_input.Shutdown();
		m_audio.Shutdown();
		m_particleSystem.Shutdown();
		m_renderer.Shutdown();
	}
}


