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

			nu::Vector2 direction = playerPosition - position;

			m_rendererCompoent->SetFlipH(direction.x < 0);

			if (playerPosition.x < position.x) dir = -1.0f;
			else dir = 1.0f;

			if (direction.Length() < 20.0f)
			{
				m_state = State::Attack;

			}

			if (dir != 0)
			{
				velocity.x = dir * 50.0f;
				m_rendererCompoent->Play("e_run");
				m_rendererCompoent->SetFlipH(dir < 0);

			}
			else
			{
				m_rendererCompoent->Play("e_idle");
			}
		}

	}
		break;
	case CharacterBase::State::Attack:
	{
		m_rendererCompoent->Play("Attack");
		auto damager = nu::Factory::Instance().Create<Damager>("DamagerPrototype");
		damager->SetPosition(GetTransform().position);
		damager->SetScale(1);
		damager->SetTag("EnemyDamager");
		m_scene->AddActor(std::move(damager));
		m_state = State::Move;
	}
		break;
	case CharacterBase::State::Hit:
		if (m_rendererCompoent->IsAnimationDone())
		{
			m_state = State::Move;
		}
		break;
	case CharacterBase::State::Death:
		m_rendererCompoent->Play("e_hit");
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
		m_rendererCompoent->Play("e_hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) m_health -= damager->GetDamage();
		if (m_health <= 0)
		{
			SetDestroyed();
			m_state = State::Death;
		}
		other->SetDestroyed();
		m_state = State::Hit;
	}
}

void EnemyController::Read(const nu::json::value_t& value)
{
	CharacterBase::Read(value);

}