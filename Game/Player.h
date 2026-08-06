#pragma once
#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc
{
	float speed{ 0.0f };
};

class Player : public nu::Actor
{
public:
	Player() = default;
	Player(const PlayerDesc& playerDesc) :
		Actor{ playerDesc },
		m_speed{ playerDesc.speed }
	{ }

	void OnCollision(Actor* other) override;


	void Update(float dt) override;

	void Draw(const class nu::Renderer& renderer) const override;

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};