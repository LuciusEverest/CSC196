#include "Player.h"
#include "Math/Math.h"
#include <fstream>
#include "Projectile.h"
#include "Scene.h" 
#include "../Game/Game.h" 
#include "Graphics/ParticleSystem.h"
#include "Math/Random.h"

void Player::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::ENEMY)
	{
		//m_destroy = true;
		m_scene->GetGame()->SetState(Game::eState::GAME_OVER);
	}
}

bool Player::Load(const std::string& filename)
{
	bool success = false;

	// open stream
	// check if stream is open
	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		// set success to true
		stream >> m_transform;

		std::string shapename;
		stream >> shapename;
		m_shape.Load(shapename);

	}

	return success;
}

void Player::Update(float dt)
{
	m_fireTimer += dt;
	if(Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0;

		Projectile* projectile = new Projectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(projectile);
	}



	//PLAYER
	//get force
	bleh::Vector2 force{ 0,0 };
	if (Core::Input::IsPressed('W')) { force = bleh::Vector2::forward * m_thrust; }
	//point force in direction of ship
	force = bleh::Vector2::Rotate(force, m_transform.angle);

	m_transform.position = m_transform.position + (m_velocity * dt);

	//add force to velocity
	m_velocity = m_velocity + (force * dt);
	m_velocity = m_velocity * 0.98f;
	//set position with velocity
	m_transform.position = m_transform.position + (m_velocity * dt);

	if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.y > 800) m_transform.position.y = 0;
	if (m_transform.position.x < 0)	m_transform.position.x = 800;
	if (m_transform.position.y < 0)	m_transform.position.y = 800;

	if (Core::Input::IsPressed('A')) m_transform.angle -= dt * bleh::DegreesToRadians(m_rotation);
	if (Core::Input::IsPressed('D')) m_transform.angle += dt * bleh::DegreesToRadians(m_rotation);


	if (force.LengthSqr() > 0)
	{
		g_particleSystem.Create(m_transform.position, m_transform.angle + bleh::PI, 20, 1, 1, bleh::Color{ 1, 1, 1 }, 100, 200);
	}

	if (Core::Input::IsPressed('E') && !m_prevButtonPress)
	{
		m_transform.position = bleh::Vector2{ bleh::random(0, 800), bleh::random(0, 600) };
		m_transform.angle = bleh::random(0, bleh::TWO_PI);
	}
	m_prevButtonPress = Core::Input::IsPressed('E');

	m_transform.Update();
}
