#include "FlyingEnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Damager.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);

	m_rendererCompoent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererCompoent);

}

void FlyingEnemyController::Update(float dt)
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

			if (direction.Length() < 20.0f)
			{
				m_state = State::Attack;
				m_rendererCompoent->Play("Attack");


				auto damager = nu::Factory::Instance().Create<Damager>("DamagerPrototype");
				damager->SetPosition(GetTransform().position);
				damager->SetScale(1);
				damager->SetTag("EnemyDamager");
				m_scene->AddActor(std::move(damager));
			}

			m_physicsComponent->ApplyForce(direction.Normalized() * 50.0f);
			m_rendererCompoent->Play("idle");

		}
	}
		break;
	case CharacterBase::State::Attack:
		m_state = State::Move;
		break;
	case CharacterBase::State::Hit:
		m_state = State::Move;
		break;
	case CharacterBase::State::Death:
		break;
	default:
		break;
	}



	CharacterBase::Update(dt);
}

void FlyingEnemyController::OnCollision(nu::Actor* other)
{
	if (nu::EqualsIgnoreCase(other->GetTag(), "PlayerDamager"))
	{
		m_state = State::Hit;
		m_rendererCompoent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(other);

		if (damager) m_health -= damager->GetDamage();

		if (m_health <= 0)
		{
			SetDestroyed();
		}

		other->SetDestroyed();
	}
}

void FlyingEnemyController::Read(const nu::json::value_t& value)
{
	CharacterBase::Read(value);

}