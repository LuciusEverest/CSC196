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
	m_scene.SetGame(this);
}

bool Game::Update(float dt)
{
	m_frameTime = dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_state = eState::INIT_GAME;
		}
		break;
	case Game::eState::INIT_GAME:
	{
		m_score = 0;
		m_lives = 3;
		m_state = eState::START_GAME;
		break;
	}
	case Game::eState::START_GAME:
	{
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
		m_state = eState::GAME;
	}
		
		break;
	case Game::eState::GAME:
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
		if (m_score > m_highScore) m_highScore = m_score;

		m_scene.Update(dt);
		break;
	case Game::eState::GAME_OVER:
		m_stateTimer += dt;
		if (m_stateTimer >= 3)
		{
			if (m_score > m_highScore) m_highScore = m_score;

			m_scene.RemoveAllActors();
			m_state = eState::TITLE;
		}
		break;
	default:
		break;
	}

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

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(bleh::Color{ 1, 0, 1 });
	graphics.DrawString(10, 10, std::to_string(m_frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frameTime).c_str());

	switch (m_state)
	{
	case Game::eState::TITLE:
		graphics.DrawString(400, 300, "ShipFighter");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
	{
		std::string score = "Score: " + std::to_string(m_score);
		graphics.DrawString(700, 10, score.c_str());
		m_scene.Draw(graphics);
	}
		break;
	case Game::eState::GAME_OVER:
		graphics.DrawString(400, 300, "Game Over");
		break;
	default:
		break;
	}

	std::string highScore = "High Score: " + std::to_string(m_highScore);
	graphics.DrawString(350, 10, highScore.c_str());

	g_particleSystem.Draw(graphics);

	/*bleh::Color c = bleh::Lerp(bleh::Color{ 1, 0, 0 }, bleh::Color{ 0, 1, 1 }, v);
	graphics.SetColor(c);
	bleh::Vector2 p = bleh::Lerp(bleh::Vector2{ 200,200 }, bleh::Vector2{ 600,200 }, v);
	graphics.DrawString(p.x, p.y, "Last Starfighter");*/

	//if(gameOver) graphics.DrawString(400, 300, "Game Over!");
}
