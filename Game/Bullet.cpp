#include "Bullet.h"
#include "Math/MathUtil.h"
#include "Core/Factory.h"
#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Bullet);

void Bullet::Update(float dt)
{
	//nu::Vector2 forward{ 1.0f, 0.0f };
	//nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DegToRad) * m_speed;
	////SetVelocity(velocity);

	auto physicsComponent = GetComponent<nu::PhysicsComponent>();


	if (physicsComponent)
	{
		nu::Vector2 forward{ 1, 0 }; //->
		nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DegToRad) * m_speed;
		physicsComponent->SetVelocity(velocity);

		nu::Vector2 position = physicsComponent->GetPosition();

		position.x = nu::math::Wrap((float)0, 1280.0f, m_transform.position.x);
		position.y = nu::math::Wrap(float(0), 1024.0f, m_transform.position.y);
		physicsComponent->SetPosition(position);

		//physicsComponent->ApplyTorque(roatate);
	}

	Actor::Update(dt);
}

void Bullet::Read(const nu::json::value_t& value)
{
	Actor::Read(value);

	JSON_READ_NAME(value, "speed", m_speed);
	JSON_READ_NAME(value, "lifespan", m_lifespan);

}