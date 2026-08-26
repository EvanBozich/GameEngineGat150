#include "Player.h"
#include "Bullet.h"
#include "Assets.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include "Math/Random.h"
#include "Components/PhysicsComponent.h"
#include "SpaceGame.h"
#include <SDL3/SDL.h>


FACTORY_REGISTER(Player);



void Player::Update(float dt)
{
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    //SetVelocity(GetVelocity() + (force * dt));
    float roatate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) roatate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) roatate = +180.0f;


    auto physicsComponent = GetComponent<nu::PhysicsComponent>();

    if (physicsComponent)
    {
        nu::Vector2 forward{ 1, 0 }; //->
        nu::Vector2 force = forward.Rotate(m_transform.rotation * nu::math::DegToRad) * thrust;
        physicsComponent->ApplyForce(force);

        physicsComponent->ApplyTorque(roatate);

        nu::Vector2 position = physicsComponent->GetPosition();

        position.x = nu::math::Wrap(0.0f, 1280.0f, position.x);
        position.y = nu::math::Wrap(0.0f, 1024.0f, position.y);
        physicsComponent->SetPosition(position);
    }


    //AddVelocity(velocity * dt);

    nu::Particle particle;
    particle.position = m_transform.position;
    particle.color = { 1.0f, 1.0f, 1.0f };
    particle.texture = nu::Resources().Get<nu::Texture>("textures/thrust.png", nu::Engine::Get().GetRenderer());
    particle.lifespan = nu::Randomfloat(0.5f, 1.5f);
    particle.velocity = { nu::Randomfloat(-200.0f, 200.0f), nu::Randomfloat(-200.0f, 200.0f) };

    nu::Engine::Get().GetPS().AddParticle(particle);

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
    {
        auto bullet = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
        bullet->SetTransform(m_transform);
        bullet->SetScale(2.0f);

        m_scene->AddActor(std::move(bullet));
    }

    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_E))
    {
        this->m_transform = nu::Transform{ nu::Vector2{nu::Randomfloat(1280), nu::Randomfloat(1024)}, 0.0f, 1.0f };
    }


    Actor::Update(dt);
}

void Player::Draw(const nu::Renderer& renderer) const
{
	Actor::Draw(renderer);
}

void Player::Read(const nu::json::value_t& value)
{
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);

}

void Player::OnCollision(Actor* other)
{
    return; //Don't die
    if (other->GetTag() == "Enemy")
    {
            SetDestroyed();
            ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();


    }
}

