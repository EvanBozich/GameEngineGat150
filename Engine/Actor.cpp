#include "pch.h"
#include "Actor.h"
#include "Texture.h"
#include "Renderer.h"
#include "MathUtil.h"
#include "Engine.h"
#include "Components/RendererComponent.h"



namespace nu 
{

    void Actor::Update(float dt)
    {
        if (m_lifespan > 0)
        {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
         
        }

        for (auto component : m_components)
        {
            component->Update(dt);
        }



        m_transform.position += (m_velocity * dt);
        m_velocity *= 1.0f / ((1.0f) + m_damping * dt);

        m_transform.position.x = nu::math::Wrap((float)0, 1280.0f, m_transform.position.x);
        m_transform.position.y = nu::math::Wrap(float(0), 1024.0f, m_transform.position.y);
    }

    void Actor::Draw(const Renderer& renderer) const
    {
        for (auto component : m_components)
        {
           auto rendererComponent = dynamic_cast<RendererComponent*>(component);

           if (rendererComponent)
           {
               rendererComponent->Draw(renderer);
           }
        }

    }

    float Actor::GetRadius() const
    {

            return 0.0f;
    }
    void Actor::Read(const json::value_t& value)
    {

        Object::Read(value);
        if (JSON_HAS_NAME(value, "transform"))
        {
            m_transform.Read(JSON_GET_NAME(value, "transform"));
        }


        JSON_READ_NAME(value, "tag", m_tag);
        JSON_READ_NAME(value, "lifespan", m_lifespan);
        JSON_READ_NAME(value, "velocity", m_velocity);
        JSON_READ_NAME(value, "damping", m_damping);

        if (JSON_HAS_NAME(value, "components"))
        {
            for (auto& componentValue : JSON_GET_NAME(value, "components").GetArray())
            {
                //get components type
                std::string typeName;
                JSON_READ_NAME(componentValue, "type", typeName);

                std::cout << "Loading component type: " << typeName << std::endl;

                //create component
                auto component = Factory::Instance().Create<Component>(typeName);

                if (component)
                {
                    component->Read(componentValue);
                }
            }
        }
    }
}