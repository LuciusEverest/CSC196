// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Color.h"
#include "core.h"
#include "Game.h"
#include "Audio/AudioSystem.h"
#include <time.h>

Game game;

bool Update(float dt) // dt:delta time = (1/60) = 0.01667 | (1/90) = 0.0111
{
	bool quit = game.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics) 
{
	game.Draw(graphics);
}

int main()
{
	//startup engine
	srand(static_cast<unsigned int>(time(NULL)));
	g_particleSystem.Startup();
	g_audioSystem.Startup();

	game.Initialize();

	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown();
	g_audioSystem.Shutdown();

	//shutdown engine
	/*g_particleSystem.Shutdown();
	scene.Shutdown();*/
}
