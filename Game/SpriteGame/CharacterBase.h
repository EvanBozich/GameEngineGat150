#pragma once
#include "Framework/Actor.h"
class CharacterBase : public nu::Actor
{
public:
	enum class State
	{
		Move,
		Attack,
		Hit,
		Death
	};

	void Read(const nu::json::value_t& value) override;

protected:
	float m_health{ 10.0f };
	float stateTimer = 0.0f;
	State m_state = State::Move;
};