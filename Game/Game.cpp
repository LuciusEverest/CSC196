// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "core.h"

bleh::Color color{ 1,0,1 };
std::vector<bleh::Vector2> points = { { 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 } };
bleh::Vector2 position{ 400.0f, 300.0f };

float speed = 5.0f;
float angle = 0.0f;
float scale = 5.0f;

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
		//position = position + (-direction * speed);
	}

	//if (Core::Input::IsPressed('A')) position += bleh::Vector2{ -1.0f, 0.0f } * speed;
	//if (Core::Input::IsPressed('D')) position += bleh::Vector2{ 1.0f, 0.0f } * speed;

	/*for (bleh::Vector2& point : points)
	{
		point = bleh::Vector2{ bleh::random(-10.0f, 10.0f), bleh::random(-10.0f, 10.0f) };
	}*/

	if (Core::Input::IsPressed('A')) angle -= dt * 3.0f;
	if (Core::Input::IsPressed('D')) angle += dt * 3.0f;

	return quit; 
}

void Draw(Core::Graphics& graphics) 
{
	
	graphics.SetColor(color.Pack888());
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
	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown();
}
