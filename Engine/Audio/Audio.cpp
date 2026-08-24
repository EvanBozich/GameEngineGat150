#include "pch.h"
#include "Audio.h"


namespace nu {

    bool Audio::Initialize()
    {
        FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem, FMOD_VERSION);
		if (!CheckFMODResult(result)) 
			return false;

		void* extradriverdata = nullptr;
		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result)) 
			return false;

		return true;
    }

	bool Audio::CheckFMODResult(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			std::cerr << result << std::endl;
			return false;
		}

		return true;
	}

	void Audio::Shutdown()
	{
		CheckFMODResult(/*TODO: release() fmod system*/m_fmodSystem->release());
	}

	void Audio::Update()
	{
		CheckFMODResult(/*TODO: update() fmod system*/m_fmodSystem->update());
	}

	bool Audio::AddSound(const std::string& name, const std::string& filename)
	{
		// check if key exists in sounds map
		if (/*TODO: check if name already exists in m_sounds*/m_sounds.contains(name))
		{
			std::cerr << "Audio System : name already exists " << name << std::endl;
			return false;
		}
		// audio->createSound("whistle.mp3", FMOD_DEFAULT, 0, &sound);

		// create sound from key
		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!CheckFMODResult(result))
			return false;

		// insert sound into map
		//TODO: add sound to m_sounds using name as key
		m_sounds.insert({ name, sound });

		return true;
	}

	bool Audio::PlaySound(const std::string& name)
	{
		// check if sound exists in sounds map
		if (!(m_sounds.contains(name)))
		{
			std::cerr << "Audio System : name doesn't exists " << name << std::endl;
			return false;
		}
		//audio->playSound(sounds[0], nullptr, false, nullptr);

		// play sound from key
		FMOD_RESULT result = m_fmodSystem->playSound(m_sounds.at(name), nullptr, false, nullptr);
		if (!CheckFMODResult(result))
			return false;

		return true;
	}
}