#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Factory.h"

namespace nu {


	void Scene::Update(float dt)
	{
		//update actor
		for (auto& actor : m_actors)
		{
			actor->Update(dt);
		}

		UpdateCollisions();

		std::erase_if(m_actors, [](auto& actor) {return actor->m_destroyed;});

		//add pending actors
		//m_actors.insert(m_actors.end(), m_pending_actors.begin(), m_pending_actors.end());
		for (auto& actor : m_pending_actors)
		{
			m_actors.push_back(std::move(actor));
		}
		m_pending_actors.clear();
	}

	void Scene::Draw(const class Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::UpdateCollisions()
	{
		for (auto& actorA : m_actors)
		{
			for (auto& actorB : m_actors)
			{
				if (actorA == actorB || actorA->m_destroyed || actorB->m_destroyed) continue;

				float distance = (actorA->m_transform.position - actorB->m_transform.position).Length();

				if (distance <= actorA->GetRadius() + actorB->GetRadius())
				{
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}

	void Scene::RemoveAllActors()
	{


		m_actors.clear();
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{ 
		actor->m_scene = this;
		m_pending_actors.push_back(std::move(actor)); 
	}

	bool Scene::Load(const std::string& sceneName)
	{
		json::document_t document;
		if (json::Load("data/scene.json", document))
		{

			if (JSON_HAS_NAME(document, "actors"))
			{
				for (auto& actorValue : JSON_GET_NAME(document, "actors").GetArray())
				{
					//get actor type
					std::string typeName;
					JSON_READ_NAME(actorValue, "type", typeName);

					//create actor
					auto actor = Factory::Instance().Create<Actor>(typeName);
					actor->Read(actorValue);

					//check prototype
					bool prototype = false;
					JSON_READ(actorValue, prototype);

					//if prototype add to factory, else add to scene
					if (prototype)
					{
						std::string name;
						JSON_READ(actorValue, name);
						Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
					}
					else
					{
						AddActor(std::move(actor));
					}
				}
			}
		}
		else
		{
			return false;
		}



		return true;
	}

}
