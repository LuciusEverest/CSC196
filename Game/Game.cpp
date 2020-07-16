// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "core.h"
#include <string>
#include "Graphics/Shape.h"
#include "Math\Transform.h"
#include "Object/Actor.h"
#include "Player.h"
#include "Enemy.h"
#include <list>

std::list<bleh::Actor*> sceneActors;

float frameTime;
float spawnTimer{ 0 };

template<typename T>
T* GetActor()
{
	T* actor{ nullptr };

	for (bleh::Actor* a : sceneActors)
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

	for (bleh::Actor* a : sceneActors)
	{
		T* actor = dynamic_cast<T*>(a);
		if (actor)
		{
			actors.push_back(actor);
		}
	}

	return actors;
}

void RemoveActor(bleh::Actor* actor)
{
	auto iter = std::find(sceneActors.begin(), sceneActors.end(), actor);
	if (iter != sceneActors.end())
	{
		delete* iter;
		sceneActors.erase(iter);
	}
}

bool Update(float dt) // dt:delta time = (1/60) = 0.01667 | (1/90) = 0.0111
{
	frameTime = dt;

	spawnTimer += dt;
	if (spawnTimer >= 3.0f)
	{
		spawnTimer = 0;

		//spawn enemy
		Enemy* enemy = new Enemy;
		enemy->Load("enemy.txt");
		enemy->SetTarget(GetActor<Player>());
		enemy->SetSpeed(bleh::random(50, 100));

		enemy->GetTransform().position = bleh::Vector2{ bleh::random(0, 800), bleh::random(0, 600) };
		sceneActors.push_back(enemy);
	}

	if (Core::Input::IsPressed(VK_SPACE))
	{
		Enemy* enemy = GetActor<Enemy>();
		RemoveActor(enemy);


		/*auto enemies = GetActors<Enemy>();
		for (Enemy* enemy : enemies)
		{
			RemoveActor(enemy);

		}*/

	}

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	for (bleh::Actor* actor : sceneActors)
	{
		actor->Update(dt);
	}

	return quit; 
}

void Draw(Core::Graphics& graphics) 
{
	graphics.SetColor(bleh::Color{ 1, 0, 1 });
	
	/*bleh::Color c = bleh::Lerp(bleh::Color{ 1, 0, 0 }, bleh::Color{ 0, 1, 1 }, v);
	graphics.SetColor(c);
	bleh::Vector2 p = bleh::Lerp(bleh::Vector2{ 200,200 }, bleh::Vector2{ 600,200 }, v);
	graphics.DrawString(p.x, p.y, "Last Starfighter");*/

	//if(gameOver) graphics.DrawString(400, 300, "Game Over!");

	for (bleh::Actor* actor : sceneActors)
	{
		actor->Draw(graphics);
	}
}

int main()
{
	/*DWORD time = GetTickCount();
	std::cout << time/1000/60/60/24 << std::endl;*/

	//initialize
	bleh::Actor* player = new Player;
	player->Load("player.txt");
	sceneActors.push_back(player);

	for (size_t i = 0; i < 10; i++)
	{
		bleh::Actor* actor = new Enemy;
		actor->Load("enemy.txt");

		Enemy* enemy = dynamic_cast<Enemy*>(actor);
		enemy->SetTarget(player);
		enemy->SetSpeed(bleh::random(50, 100));

		actor->GetTransform().position = bleh::Vector2{ bleh::random(0, 800), bleh::random(0, 600) };
		sceneActors.push_back(actor);
	}

	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown();
}
