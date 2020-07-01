// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "core.h"

const size_t NUM_POINTS = 40;
std::vector<bleh::Vector2> points;
bleh::Vector2 position{ 400.0f, 300.0f };
float speed = 5.0f;

bool Update(float dt) 
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);

	bleh::Vector2 target = bleh::Vector2{ x, y };
	bleh::Vector2 direction = target - position; //head - tail <-

	direction.Normalize();

	//if (direction.Length() < 50.0f)
	{
		position = position + (-direction * speed);
	}

	//if (Core::Input::IsPressed('A')) position += bleh::Vector2{ -1.0f, 0.0f } * speed;
	//if (Core::Input::IsPressed('D')) position += bleh::Vector2{ 1.0f, 0.0f } * speed;

	for (bleh::Vector2& point : points)
	{
		point = bleh::Vector2{ bleh::random(-10.0f, 10.0f), bleh::random(-10.0f, 10.0f) };
	}

	return quit; 
}

void Draw(Core::Graphics& graphics) 
{
	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//graphics.DrawLine(bleh::random(0.0f, 800.0f), bleh::random(0.0f, 600.0f), bleh::random(0.0f, 800.0f), bleh::random(0.0f, 600.0f));

	for (size_t i = 0; i < NUM_POINTS - 1; i +=2)
	{
		bleh::Vector2 p1 = position + points[i] * 4.0f;
		bleh::Vector2 p2 = position + points[i + 1] * 4.0f;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

int main()
{
	for (size_t i = 0; i < NUM_POINTS; i++)
	{
		points.push_back({ bleh::random(0.0f, 800.0f), bleh::random(0.0f, 600.0f) });
	}
	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown();
}
