#include "Enemy.h"
#include "Renderer.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"

void Enemy::Update(float dt)
{
    Player* player = m_scene->GetActorByName<Player>("Player");

    if (player)
    {
        nu::Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        m_transform.rotation = rotation * nu::math::RadToDeg;

        nu::Vector2 forward{ 1,0 };
        forward = forward.Rotate(m_transform.rotation * nu::math::DegToRad);
        AddVelocity(forward * m_speed * dt);
    }

    float thrust = 0.0f;
    float roatate = 0.0f;

    nu::Vector2 forward{ 1, 0 }; //->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DegToRad) * thrust;
    AddVelocity(velocity * dt);


    Actor::Update(dt);
}

void Enemy::Draw(const nu::Renderer& renderer) const
{
    Actor::Draw(renderer);
}

void Enemy::OnCollision(Actor* other)
{
    if (other->GetTag() == "Bullet")
    {
        SetDestroyed();
        other->SetDestroyed();

        ((SpaceGame*)m_scene->GetGame())->AddPoints(100);

        // create particle explosion
        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            particle.color = { 1.0f, 1.0f, 1.0f };
            particle.lifespan = nu::Randomfloat(0.5f, 2.0f);
            particle.velocity = { nu::Randomfloat(-600.0f, 600.0f), nu::Randomfloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }
    }
}
    

