#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Damager.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);

	m_rendererCompoent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererCompoent);

}

void PlayerController::Update(float dt)
{
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();
	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
		float dir = 0.0f;

		if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1.0f;
		if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = 1.0f;
		if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_rendererCompoent->Play("h_jump", true);
			std::cout << "Called the jump animaition" << std::endl;
			velocity.y = -500.0f;
		}
		if (dir != 0.0f)
		{
			m_rendererCompoent->Play("h_run");
			velocity.x = dir * 100.0f;
			m_rendererCompoent->SetFlipH(dir < 0);
		}
		else
		{
			m_rendererCompoent->Play("h_idle");
		}

		if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_X))
		{
			m_rendererCompoent->Play("h_attack");
			m_state = State::Attack;

			auto damager = nu::Factory::Instance().Create<Damager>("DamagerPrototype");
			if (dir > 0 || dir == 0)
			{
				damager->SetPosition(GetTransform().position + nu::Vector2{20.0f, 0.0f});
			}
			else
			{
				damager->SetPosition(GetTransform().position - nu::Vector2{ 20.0f, 0.0f });
			}
			damager->SetTag("PlayerDamager");
			m_scene->AddActor(std::move(damager));
		}
	}
		break;
	case CharacterBase::State::Attack:
	{
		if (m_rendererCompoent->IsAnimationDone())
		{
			m_rendererCompoent->Play("h_idle");
			m_state = State::Move;
		}
	}
		break;
	case CharacterBase::State::Hit:
		m_rendererCompoent->Play("h_hit");
		break;
	case CharacterBase::State::Death:
		m_rendererCompoent->Play("h_death");
		break;
	default:
		break;
	}



	m_physicsComponent->SetVelocity(velocity);
	nu::Engine::Get().GetRenderer().SetCamera(m_physicsComponent->GetPosition());

	CharacterBase::Update(dt);
}

void PlayerController::OnCollision(nu::Actor* other)
{
	if (nu::EqualsIgnoreCase(other->GetTag(), "EnemyDamager"))
	{
		m_rendererCompoent->Play("h_death");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) m_health -= damager->GetDamage();
		if (m_health <= 0)
		{
			m_state = State::Death;
		}
		other->SetDestroyed();
		m_state = State::Hit;
	}
}

void PlayerController::Read(const nu::json::value_t& value)
{
	CharacterBase::Read(value);

}
