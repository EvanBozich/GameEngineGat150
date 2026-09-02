#include "EnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Damager.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);

	m_rendererCompoent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererCompoent);

}

void EnemyController::Update(float dt)
{
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();


	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
		float dir = 0.0f;

		auto player = m_scene->GetActorByName("PlayerPrototype");
		if (player)
		{
			nu::Vector2 position = GetTransform().position;
			nu::Vector2 playerPosition = player->GetTransform().position;

			if (playerPosition.x < position.x) dir = -1.0f;
			else dir = 1.0f;
		}



		if (dir != 0)
		{
			velocity.x = dir * 50.0f;
			m_rendererCompoent->Play("run");
			m_rendererCompoent->SetFlipH(dir < 0);

		}
		else
		{
			m_rendererCompoent->Play("idle");
		}

	}
		break;
	case CharacterBase::State::Attack:
		break;
	case CharacterBase::State::Hit:
		if (m_rendererCompoent->IsAnimationDone())
		{
			m_state = State::Move;
			m_rendererCompoent->Play("idle");
		}
		break;
	case CharacterBase::State::Death:
		break;
	default:
		break;
	}


	m_physicsComponent->SetVelocity(velocity);

	CharacterBase::Update(dt);
}

void EnemyController::OnCollision(nu::Actor* other)
{
	if (nu::EqualsIgnoreCase(other->GetTag(), "PlayerDamager"))
	{
		m_state = State::Hit;
		m_rendererCompoent->Play("e_hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) m_health -= damager->GetDamage();
		if (m_health <= 0)
		{
			SetDestroyed();
		}
	}
}

void EnemyController::Read(const nu::json::value_t& value)
{
	CharacterBase::Read(value);

}