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

bleh::Actor player;
bleh::Actor enemy;

//bleh::Shape ship;
//bleh::Transform transform{ {400, 300}, 4, 0 };

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

	//get force
	bleh::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = bleh::Vector2::forward * thrust; }
	//point force in direction of ship
	force = bleh::Vector2::Rotate(force, player.GetTransform().angle);

	bleh::Vector2 direction = force * dt; 

	player.GetTransform().position = player.GetTransform().position + direction;

	//add force to velocity
	velocity = velocity + (force * dt);
	velocity = velocity * 0.98f;
	//set position with velocity
	player.GetTransform().position = player.GetTransform().position + (velocity * dt);

	//transform.position = bleh::Clamp(transform.position, bleh::Vector2{ 0,0 }, bleh::Vector2{ 800, 600 });

	//transform.position.x = bleh::Clamp(transform.position.x, 0.0f, 800.0f);
	//transform.position.y = bleh::Clamp(transform.position.y, 0.0f, 800.0f);


	if (player.GetTransform().position.x > 800) player.GetTransform().position.x = 0;
	if (player.GetTransform().position.y > 800) player.GetTransform().position.y = 0;
	if (player.GetTransform().position.x < 0)	player.GetTransform().position.x = 800;
	if (player.GetTransform().position.y < 0)	player.GetTransform().position.y = 800;

	//if (Core::Input::IsPressed('A')) position += bleh::Vector2::left * (speed * dt);
	//if (Core::Input::IsPressed('D')) position += bleh::Vector2::right * (speed * dt);

	if (Core::Input::IsPressed('A')) player.GetTransform().angle -= dt * bleh::DegreesToRadians(360.0f);
	if (Core::Input::IsPressed('D')) player.GetTransform().angle += dt * bleh::DegreesToRadians(360.0f);

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
	
	//ship.Draw(graphics, transform);
	player.Draw(graphics);
	enemy.Draw(graphics);
}

int main()
{
	DWORD time = GetTickCount();
	std::cout << time/1000/60/60/24 << std::endl;

	//ship.Load("ship.txt");
	player.Load("player.txt");
	enemy.Load("enemy.txt");

	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown();
}
