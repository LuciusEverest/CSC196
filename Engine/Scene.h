#pragma once
#include "Object/Actor.h"
#include <vector>
#include <core.h>
#include <list>

class Game;

namespace bleh
{
	class Scene
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		template<typename T>
		T* GetActor()
		{
			T* actor{ nullptr };

			for (bleh::Actor* a : m_actors)
			{
				actor = dynamic_cast<T*>(a);
				if (actor != nullptr)break;
			}

			return actor;
		}

		template<typename T>
		std::vector<T*> GetActors()
		{
			std::vector<T*> actors;

			for (bleh::Actor* a : m_actors)
			{
				T* actor = dynamic_cast<T*>(a);
				if (actor)
				{
					actors.push_back(actor);
				}
			}

			return actors;
		}

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* actor);
		void RemoveAllActors();

		void SetGame(Game* game) { m_game = game; }
		Game* GetGame() { return m_game; }

	private:
		Game* m_game;
		std::list<class Actor*> m_actors;
	};
}