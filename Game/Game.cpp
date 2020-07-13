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

Player player;
Enemy enemy;

float speed = 300.0f;
bleh::Vector2 velocity;
float thrust = 300.0f;

float frameTime;
float roundTime{ 0 };
bool gameOver{ false };

float t{ 0 };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt) // dt:delta time = (1/60) = 0.01667 | (1/90) = 0.0111
{
	frameTime = dt;
	roundTime += dt;
	if (roundTime >= 5) gameOver = true;

	//dt *= 2; //speed up
	//dt *= -dt; //reverse controls
	//if (gameOver) dt = 0;

	t = t + (dt * 5.0f);

	//get delta time
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);

	//bleh::Vector2 target = bleh::Vector2{ x, y };
	//bleh::Vector2 direction = target - position; //head - tail <-

	//direction.Normalize();

	//PLAYER
	player.Update(dt);
	
	//ENEMY
	enemy.Update(dt);

	return quit; 
}

void Draw(Core::Graphics& graphics) 
{
	graphics.SetColor(bleh::Color{ 1, 0, 1 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f/frameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime/1000.0f).c_str());
	
	float v = (std::sin(t) + 1.0f) * 0.5f; // (-1 <-> 1) -> (0 - 2)

	bleh::Color c = bleh::Lerp(bleh::Color{ 1, 0, 0 }, bleh::Color{ 0, 1, 1 }, v);
	graphics.SetColor(c);
	bleh::Vector2 p = bleh::Lerp(bleh::Vector2{ 200,200 }, bleh::Vector2{ 600,200 }, v);
	graphics.DrawString(p.x, p.y, "Last Starfighter");

	//if(gameOver) graphics.DrawString(400, 300, "Game Over!");
	
	player.Draw(graphics);
	enemy.Draw(graphics);
}

int main()
{
	DWORD time = GetTickCount();
	std::cout << time/1000/60/60/24 << std::endl;

	player.Load("player.txt");
	enemy.Load("enemy.txt");

	enemy.SetTarget(&player);

	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown();
}
