#include "Enemy.h"
#include <fstream>
#include "Graphics/ParticleSystem.h"  
#include "Audio/AudioSystem.h"  
#include "Scene.h"  
#include "../Game/Game.h"  
#include <Math\Math.h>

bool Enemy::Load(const std::string& filename)
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

void Enemy::Update(float dt)
{
	bleh::Vector2 targetPosition = (m_target) ? m_target->GetTransform().position : bleh::Vector2{ 400, 300 };
	bleh::Vector2 direction = targetPosition - m_transform.position;
	direction.Normalize();
	bleh::Vector2 velocity = direction * m_speed;
	m_transform.position = m_transform.position + (velocity * dt);
	m_transform.angle = std::atan2(direction.y, direction.x) + bleh::DegreesToRadians(90.0f);

	m_transform.Update();
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PROJECTILE)
	{
		m_destroy = true;
		g_audioSystem.PlayAudio("Enemy_Hurt");

		// set game points/score
		m_scene->GetGame()->AddPoints(100);

		bleh::Color colors[] = { {1,1,0}, {1,0,0}, {0,1,1} };
		bleh::Color color = colors[rand() % 3];
		g_particleSystem.Create(m_transform.position, 0, 180, 30, 1, color, 100, 200);

	}
}
