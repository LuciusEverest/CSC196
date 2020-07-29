#include "Game.h"
#include <string>
#include "Graphics/Shape.h"
#include "Math\Transform.h"
#include "Object/Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include <list>
#include <Scene.h>
#include <Math\Random.h>
#include "Actors/Locator.h"
#include <Math\Math.h>




void Game::Initialize()
{
	/*DWORD time = GetTickCount();
		std::cout << time/1000/60/60/24 << std::endl;*/
	
	g_audioSystem.AddAudio("Laser1", "Laser1.wav");
	g_audioSystem.AddAudio("Explosion1", "Explosion1.wav");
	g_audioSystem.AddAudio("Enemy_Hurt", "Enemy_Hurt.wav");
	g_audioSystem.AddAudio("Powerup1", "Powerup1.wav");
	g_audioSystem.AddAudio("Select1", "Select1.wav");

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
			g_audioSystem.PlayAudio("Select1");
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

		Locator* locator = new Locator;
		locator->GetTransform().position = bleh::Vector2{ 2, 2 };
		player->AddChild(locator);
		
		locator = new Locator;
		locator->GetTransform().position = bleh::Vector2{ -2, 2 };
		player->AddChild(locator);

		for (size_t i = 0; i < 10; i++)
			{
				bleh::Actor* actor = new Enemy;
				actor->Load("enemy.txt");
				Enemy* enemy = dynamic_cast<Enemy*>(actor);
				enemy->SetTarget(player);
				enemy->SetSpeed(bleh::random(50, 100));
				float distance = bleh::random(300, 200);
				float angle = bleh::random(0, bleh::TWO_PI);
				bleh::Vector2 position = bleh::Vector2::Rotate({ 0.0f, distance }, angle);
				actor->GetTransform().position = m_scene.GetActor<Player>()->GetTransform().position + position;
				
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

			float distance = bleh::random(300, 200);
			float angle = bleh::random(0, bleh::TWO_PI);
			bleh::Vector2 position = bleh::Vector2::Rotate({ 0.0f, distance }, angle);
			enemy->GetTransform().position = m_scene.GetActor<Player>()->GetTransform().position + position;

			m_scene.AddActor(enemy);
		}
		if (m_score > m_highScore) m_highScore = m_score;

		break;
	case Game::eState::PLAYER_DEAD:
		m_lives = m_lives - 1;
		m_state = (m_lives <= 0) ? eState::GAME_OVER : eState::GAME_WAIT;
		m_stateTimer = 3;
		break;
	case Game::eState::GAME_WAIT:
		
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene.RemoveAllActors();
			m_state = eState::START_GAME;
			g_audioSystem.PlayAudio("End_Timer");
		}
		break;
	case Game::eState::GAME_OVER:
		
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			if (m_score > m_highScore) m_highScore = m_score;

			m_scene.RemoveAllActors();
			m_state = eState::TITLE;
			g_audioSystem.PlayAudio("Game_Over");
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

	m_scene.Update(dt);
	g_particleSystem.Update(dt);
	g_audioSystem.Update(dt);

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
		
	}
		break;
	case Game::eState::GAME_OVER:
		graphics.DrawString(400, 300, "Game Over");
		break;
	default:
		break;
	}

	std::string score = "Score: " + std::to_string(m_score);
	graphics.DrawString(700, 10, score.c_str());
		
	std::string lives = "Lives: " + std::to_string(m_lives);
	graphics.DrawString(700, 25, lives.c_str());

	score = "High Score: " + std::to_string(m_highScore);
	graphics.DrawString(350, 10, score.c_str());
	
	m_scene.Draw(graphics);
	g_particleSystem.Draw(graphics);

}
