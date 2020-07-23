#include "Game.h"
#include <string>
#include "Graphics/Shape.h"
#include "Math\Transform.h"
#include "Object/Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Graphics/ParticleSystem.h"
#include <list>
#include <Scene.h>
#include <Math\Random.h>

void Game::Initialize()
{
	/*DWORD time = GetTickCount();
		std::cout << time/1000/60/60/24 << std::endl;*/

	//intialize engine
	m_scene.Startup();
	g_particleSystem.Startup();

	Player* player = new Player;
	player->Load("player.txt");
	m_scene.AddActor(player);

	for (size_t i = 0; i < 10; i++)
	{
		bleh::Actor* actor = new Enemy;
		actor->Load("enemy.txt");

		Enemy* enemy = dynamic_cast<Enemy*>(actor);
		enemy->SetTarget(player);
		enemy->SetSpeed(bleh::random(50, 100));

		actor->GetTransform().position = bleh::Vector2{ bleh::random(0, 800), bleh::random(0, 600) };
		m_scene.AddActor(actor);
	}
}

bool Game::Update(float dt)
{
	m_frameTime = dt;

	m_spawnTimer += dt;
	if (m_spawnTimer >= 3.0f)
	{
		m_spawnTimer = 0;

		//spawn enemy
		Enemy* enemy = new Enemy;
		enemy->Load("enemy.txt");
		enemy->SetTarget(m_scene.GetActor<Player>());
		enemy->SetSpeed(bleh::random(50, 100));

		enemy->GetTransform().position = bleh::Vector2{ bleh::random(0, 800), bleh::random(0, 600) };
		m_scene.AddActor(enemy);
	}

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		bleh::Color colors[] = { {1,1,1}, {1,0,0}, {1,1,0}, {0,1,1} };
		bleh::Color color = colors[rand() % 4];
		g_particleSystem.Create({ x,y }, 0, 180, 30, 1, color, 100, 200);

	}

	if (Core::Input::IsPressed('Z'))
	{
		bleh::Color colors[] = { {1,1,1}, {1,0,0}, {0,1,1} };
		bleh::Color color = colors[rand() % 3];
		g_particleSystem.Create({ x,y }, 0, 180, 30, 1, color, 100, 200);

	}

	g_particleSystem.Update(dt);
	m_scene.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(bleh::Color{ 1, 0, 1 });
	graphics.DrawString(10, 10, std::to_string(m_frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frameTime).c_str());

	g_particleSystem.Draw(graphics);
	m_scene.Draw(graphics);

	/*bleh::Color c = bleh::Lerp(bleh::Color{ 1, 0, 0 }, bleh::Color{ 0, 1, 1 }, v);
	graphics.SetColor(c);
	bleh::Vector2 p = bleh::Lerp(bleh::Vector2{ 200,200 }, bleh::Vector2{ 600,200 }, v);
	graphics.DrawString(p.x, p.y, "Last Starfighter");*/

	//if(gameOver) graphics.DrawString(400, 300, "Game Over!");
}
