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
#include <Scene.h>

bleh::Scene scene;

float frameTime;
float spawnTimer{ 0 };


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
		enemy->SetTarget(scene.GetActor<Player>());
		enemy->SetSpeed(bleh::random(50, 100));

		enemy->GetTransform().position = bleh::Vector2{ bleh::random(0, 800), bleh::random(0, 600) };
		scene.AddActor(enemy);
	}

	//if (Core::Input::IsPressed(VK_SPACE))
	//{
	//	Enemy* enemy = scene.GetActor<Enemy>();
	//	scene.RemoveActor(enemy);


	//	/*auto enemies = GetActors<Enemy>();
	//	for (Enemy* enemy : enemies)
	//	{
	//		RemoveActor(enemy);

	//	}*/

	//}

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	scene.Update(dt);

	return quit; 
}

void Draw(Core::Graphics& graphics) 
{
	graphics.SetColor(bleh::Color{ 1, 0, 1 });
	
	scene.Draw(graphics);

	/*bleh::Color c = bleh::Lerp(bleh::Color{ 1, 0, 0 }, bleh::Color{ 0, 1, 1 }, v);
	graphics.SetColor(c);
	bleh::Vector2 p = bleh::Lerp(bleh::Vector2{ 200,200 }, bleh::Vector2{ 600,200 }, v);
	graphics.DrawString(p.x, p.y, "Last Starfighter");*/

	//if(gameOver) graphics.DrawString(400, 300, "Game Over!");

}

int main()
{
	/*DWORD time = GetTickCount();
	std::cout << time/1000/60/60/24 << std::endl;*/

	scene.Startup();

	//initialize
	bleh::Actor* player = new Player;
	player->Load("player.txt");
	scene.AddActor(player);

	for (size_t i = 0; i < 10; i++)
	{
		bleh::Actor* actor = new Enemy;
		actor->Load("enemy.txt");

		Enemy* enemy = dynamic_cast<Enemy*>(actor);
		enemy->SetTarget(player);
		enemy->SetSpeed(bleh::random(50, 100));

		actor->GetTransform().position = bleh::Vector2{ bleh::random(0, 800), bleh::random(0, 600) };
		scene.AddActor(actor);
	}

	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown();
}
