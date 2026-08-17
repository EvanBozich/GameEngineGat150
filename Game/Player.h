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

	CLASS_PROTOTYPE(Player)


	void OnCollision(Actor* other) override;


	void Update(float dt) override;

	void Draw(const class nu::Renderer& renderer) const override;

	virtual void Read(const nu::json::value_t& value) override;

	float GetSpeed() { return m_speed; }
private:
	float m_speed = 800.0f;
};