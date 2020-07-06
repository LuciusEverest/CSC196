// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "core.h"
#include <string>

bleh::Color color{ 1,0,1 };
std::vector<bleh::Vector2> points = { { 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 } };
bleh::Vector2 position{ 400.0f, 300.0f };

float speed = 300.0f;
float angle = 0.0f;
float scale = 5.0f;

float frameTime;
float roundTime{ 0 };
bool gameOver{ false };
DWORD prevTime;
DWORD deltaTime;

bool Update(float dt) // dt:delta time = (1/60) = 0.01667 | (1/90) = 0.0111
{
	frameTime = dt;
	roundTime += dt;
	if (roundTime >= 5) gameOver = true;

	//dt *= 2; //speed up
	//dt *= -dt; //reverse controls
	if (gameOver) dt = 0;

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

	bleh::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = bleh::Vector2::forward * speed; }
	bleh::Vector2 direction = force * dt; 
	direction = bleh::Vector2::Rotate(direction, angle);

	position = position + direction;

	if (position.x > 800) position.x = 0;
	if (position.y > 800) position.y = 0;
	if (position.x < 0) position.x = 800;
	if (position.y < 0) position.y = 800;

	//if (direction.Length() < 50.0f)
	{
		//position = position + (-direction * speed);
	}

	//if (Core::Input::IsPressed('A')) position += bleh::Vector2::left * (speed * dt);
	//if (Core::Input::IsPressed('D')) position += bleh::Vector2::right * (speed * dt);

	/*for (bleh::Vector2& point : points)
	{
		point = bleh::Vector2{ bleh::random(-10.0f, 10.0f), bleh::random(-10.0f, 10.0f) };
	}*/

	if (Core::Input::IsPressed('A')) angle -= dt * bleh::TWO_PI;
	if (Core::Input::IsPressed('D')) angle += dt * bleh::TWO_PI;

	return quit; 
}

void Draw(Core::Graphics& graphics) 
{

	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f/frameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime/1000.0f).c_str());
	
	if(gameOver) graphics.DrawString(400, 300, "Game Over!");
	graphics.SetColor(color);
	//graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//graphics.DrawLine(bleh::random(0.0f, 800.0f), bleh::random(0.0f, 600.0f), bleh::random(0.0f, 800.0f), bleh::random(0.0f, 600.0f));

	for (size_t i = 0; i < points.size() - 1; i ++)
	{
		bleh::Vector2 p1 = points[i];
		bleh::Vector2 p2 = points[i + 1];
		
		//transofrm
		//scale
		p1 = p1 * scale;
		p2 = p2 * scale;
		//rotate
		p1 = bleh::Vector2::Rotate(p1, angle);
		p2 = bleh::Vector2::Rotate(p2, angle);
		//translate
		p1 = p1 + position;
		p2 = p2 + position;
		
		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

int main()
{
	DWORD time = GetTickCount();
	std::cout << time/1000/60/60/24 << std::endl;

	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown();
}
