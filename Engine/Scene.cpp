#include "pch.h"
#include "Scene.h"
#include "Object/Actor.h"

namespace bleh
{
	void bleh::Scene::Startup()
	{
		//nothing
	}

	void bleh::Scene::Shutdown()
	{
		for (Actor* actor : m_actors)
		{
			delete actor;
		}
		// iterate through the actors and call delete on each actor
		// this will free up the memory for each actor
	
		m_actors.clear(); // clear m_actors list
	}

	void bleh::Scene::Update(float dt)
	{
		for (Actor* actor : m_actors)
		{
			actor->Update(dt);
		}
		// iterate through the actors and call Update on each actor}
	}

	void bleh::Scene::Draw(Core::Graphics& graphics)
	{
		// actors -> (actor) (actor) (actor) (actor)
		//			 (actor) (actor) (actor) (actor)
		// check for collision
		std::vector<Actor*> actors{ m_actors.begin(), m_actors.end() };
		for (size_t i = 0; i < actors.size(); i++)
		{
			for (size_t j = 0; j < actors.size(); j++)
			{
				float distance = bleh::Vector2::Distance(actors[i]->GetTransform().position, actors[j]->GetTransform().position);
				if (distance <= (actors[i]->GetRadius() + actors[j]->GetRadius()))
				{
					actors[i]->OnCollision(actors[j]);
					actors[j]->OnCollision(actors[i]);
				}
			}
		}

		//remove destroyed actors
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			if ((*iter)->IsDestroyed())
			{
				delete(*iter);
				iter = m_actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		for (Actor* actor : m_actors)
		{
			actor->Draw(graphics);
		}
		//iterate through the actors and call Draw on each actor
	}

	void bleh::Scene::AddActor(Actor* actor)
	{
		actor->SetScene(this);
		m_actors.push_back(actor);// push back the actor on the actors list
	}

	void bleh::Scene::RemoveActor(Actor* actor)
	{
		std::list<Actor*>::iterator iter = std::find(m_actors.begin(), m_actors.end(), actor);
		if (iter != m_actors.end())
		{
			delete* iter; m_actors.erase(iter); 
		}
	}
}
