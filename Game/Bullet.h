#pragma once
#include "Actor.h"

struct BulletDesc : public nu::ActorDesc
{
	float speed{ 0.0f };
};

class Bullet : public nu::Actor
{
public:
	Bullet() = default;
	Bullet(const BulletDesc& bulletDesc) :
		Actor{ bulletDesc },
		m_speed{ bulletDesc.speed }
	{}



	void Update(float dt) override;

	//void Draw(const class nu::Renderer& renderer) const override;
	virtual void Read(const nu::json::value_t& value) override;

	CLASS_PROTOTYPE(Bullet)


private:
	float m_speed = 800.0f;
	float m_lifespan = 1.0f;
};